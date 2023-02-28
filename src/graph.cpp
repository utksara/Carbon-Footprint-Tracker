// #include  "carbon_footprint.h"
#include "graph.h"

Graph::Graph()
{
    lastID = 0;
}

std::map<ID, std::shared_ptr<Node>> Graph::getNodes() const
{
    return this->nodes;
}

std::map<ID, std::vector<ID>> Graph::getEdges() const
{
    return this->edges;
}

bool Graph::nodeExists(ID id)
{
    if (this->edges.find(id) == this->edges.end())
    {
        return false;
    }
    return true;
}

bool Graph::nodeExists(conststr name)
{
    if (this->getNodeByName(name) == nullptr)
    {
        return false;
    }
    return true;
}

std::shared_ptr<Node> Graph::getNodeByID(ID id) const
{
    return nodes.at(id);
}

std::shared_ptr<Node> Graph::getNodeByName(conststr name) const
{
    for (std::pair<ID, std::shared_ptr<Node>> node : nodes)
    {
        if (node.second->getName() == name)
        {
            return node.second;
        }
    }
    return nullptr;
}

void Graph::addNode(std::shared_ptr<Node> node)
{
    this->nodes.insert(std::pair<ID, std::shared_ptr<Node>>(node->getID(), node));
}

void Graph::addDefaultEdge(ID id1)
{
    if (!this->nodeExists(id1))
    {
        this->edges.insert(std::pair<ID, std::vector<ID>>{id1, std::vector<ID>{}});
    }
}

void Graph::addEdge(ID id1, ID id2)
{
    this->edges.at(id1).push_back(id2);
}

std::vector<ID> Graph::getEdgesAt(ID id) const
{

    std::vector<ID> edges;
    if (this->edges.find(id) != this->edges.end())
    {
        edges = this->edges.at(id);
    }
    return edges;
}

void Graph::showEdgesAt(ID id)
{
    std::vector<ID> elements = Graph::getEdgesAt(id);
    std::cout << "\n"
              << " Items in node " << id << " are - ";
    if (!elements.empty())
    {
        for (ID parentID : elements)
        {
            std::cout << "\n"
                      << id << "-->" << parentID;
        }
    }
}

void Graph::showNodes()
{
    std::map<ID, std::shared_ptr<Node>>::iterator i;
    for (i = nodes.begin(); i != nodes.end(); i++)
    {
        std::cout << "\n"
                  << i->first << " : " << i->second->getName();
    }
}

void Graph::showEdges()
{
    std::map<ID, std::vector<ID>>::iterator i;
    for (i = this->edges.begin(); i != this->edges.end(); i++)
    {
        ID id = i->first;
        showEdgesAt(id);
        std::cout << "\n";
    }
}

std::vector<ID> Graph::getParentNodeIds(ID itemId) const
{
    std::vector<ID> parentIds;
    for (ID parentID : this->getEdgesAt(itemId))
    {
        parentIds.push_back(parentID);
    }
    return parentIds;
}

std::vector<ID> Graph::getRootNodes()
{
    std::vector<ID> rootNodes;
    std::string hasIntoEdge = "hasIntoEdge";
    this->addAttribute(hasIntoEdge, false);
    for (auto i = this->edges.begin(); i != this->edges.end(); i++)
    {
        ID id1 = i->first;
        for (ID id2 : this->getEdgesAt(id1))
        {
            this->setAttribute<bool>(hasIntoEdge, id2, true);
        }
    }

    for (auto i = this->nodes.begin(); i != this->nodes.end(); i++)
    {
        ID id = i->first;
        if (!this->getAttribute<bool>(hasIntoEdge, id))
        {
            rootNodes.push_back(id);
        }
    }
    removeAttribute(hasIntoEdge);
    return rootNodes;
}

std::vector<ID> Graph::getLeafNodes()
{
    std::vector<ID> leafNodes;
    std::string hasOutEdge = "hasOutEdge";
    this->addAttribute(hasOutEdge, false);
    for (auto i = this->edges.begin(); i != this->edges.end(); i++)
    {
        ID id = i->first;
        if (i->second.size() > 0)
        {
            this->setAttribute<bool>(hasOutEdge, id, true);
        }
    }

    for (auto i : this->getNodes())
    {
        ID id = i.first;
        if (!this->getAttribute<bool>(hasOutEdge, id))
        {
            leafNodes.push_back(id);
        }
    }
    removeAttribute(hasOutEdge);
    return leafNodes;
}

void Graph::mapAttribute(const std::string attributeName, TranformationFunction transformation)
{
    for (ID id : this->getRootNodes())
    {
        _mapAttributePerNode(id, attributeName, transformation);
    }
}

float Graph::_mapAttributePerNode(ID id, const std::string attributeName, TranformationFunction transformation, int _recursiveCallNo)
{
    if (_recursiveCallNo == 0)
    {
        this->addAttribute("visited", false);
    }
    if (!getAttribute<bool>("visited", id))
    {
        setAttribute<bool>("visited", id, true);
        for (ID parentId : this->getParentNodeIds(id))
        {
            _mapAttributePerNode(parentId, attributeName, transformation, ++_recursiveCallNo);
            this->setAttribute(attributeName, id, transformation(this->getAttribute<float>(attributeName, id), this->getNodeByID(id)->getName(), this->getNodeByID(parentId)->getName()));
        }
        return this->getAttribute<float>(attributeName, id);
    }
    if (_recursiveCallNo == 0)
    {
        this->removeAttribute("visited");
    }
    return this->getAttribute<float>(attributeName, id);
}

/*atrribute operations*/
void Graph::addAttribute(conststr name, Attribute *attribute)
{
    this->attributes.insert(std::pair<std::string, Attribute *>{name, attribute});
}

void Graph::addAttribute(conststr name, float initialValue)
{
    FloatAttribute *a = new FloatAttribute();
    for (auto node : nodes)
    {
        a->add(node.first, initialValue);
    }
    this->attributes.insert(std::pair<std::string, Attribute *>{name, a});
}

void Graph::addAttribute(conststr name, bool initialValue)
{
    BoolAttribute *b = new BoolAttribute();
    for (auto node : nodes)
    {
        b->add(node.first, initialValue);
    }
    this->attributes.insert(std::pair<std::string, Attribute *>{name, b});
}

bool Graph::hasAttribute(conststr name)
{
    return (this->attributes.find(name) != this->attributes.end());
}

void Graph::removeAttribute(conststr name)
{
    this->attributes.erase(name);
}

float Graph::reduce(conststr attributeName)
{
    return this->attributes.at(attributeName)->reduce();
}

float Graph::reduce(conststr attributeName, std::vector<ID> ids)
{
    return this->attributes.at(attributeName)->reduce(ids);
}
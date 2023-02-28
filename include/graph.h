#ifndef GRAPH_H
#define GRAPH_H

#include "float_attribute.h"
#include "bool_attribute.h"
#include <map>
#include <functional>
#include <vector>

#define AttributeTemp std::map<ID, float>
#define NodeIDs ID
#define TranformationFunction std::function<float(float, conststr childName, conststr parentName)>

typedef std::function<float(float)> AttributeFunction;
class Graph
{
private:
    ID lastID;
    std::map<ID, std::vector<ID>> edges;
    std::map<ID, std::shared_ptr<Node>> nodes;
    std::map<std::string, Attribute *> attributes;
    void addAttribute(conststr name, Attribute *attribute);

protected:
    void addDefaultEdge(ID id1);
    float _mapAttributePerNode(ID id, const std::string attributeName, TranformationFunction transformation, int _recursiveCallNo = 0);

public:
    explicit Graph();
    void addNode(std::shared_ptr<Node> node);
    void addEdge(ID x1, ID x2);
    void showEdges();
    void showEdgesAt(ID id);
    void showNodes();
    bool nodeExists(ID id);
    bool nodeExists(conststr name);
    std::shared_ptr<Node> getNodeByID(ID id) const;
    std::shared_ptr<Node> getNodeByName(conststr name) const;
    std::vector<ID> getEdgesAt(ID id) const;
    std::vector<ID> getRootNodes();
    std::vector<ID> getLeafNodes();
    std::map<ID, std::vector<ID>> getEdges() const;
    std::map<ID, std::shared_ptr<Node>> getNodes() const;
    std::vector<ID> getParentNodeIds(ID itemId) const;

    /*graph algorithms*/
    void mapAttribute(const std::string attributeName, TranformationFunction transformation);
    float reduce(conststr attributeName);
    float reduce(conststr attributeName, std::vector<ID> ids);

    /*atrribute operations*/
    void addAttribute(conststr name, float initialValue);
    void addAttribute(conststr name, bool initialValue);
    bool hasAttribute(conststr name);
    void removeAttribute(conststr name);

    template <typename T>
    void setAttribute(conststr name, ID id, T value)
    {
        try
        {
            this->attributes.at(name)->set(id, value);
        }
        catch (const std::exception &e)
        {
            throw std::invalid_argument(" In function setAttribute " + name + " for id " + std::to_string(id) + " doesn't exist");
        }
    }

    template <typename T>
    void setAttribute(conststr name, std::vector<ID> ids, T value)
    {
        for (ID id : ids)
        {
            setAttribute<T>(name, id, value);
        }
    }

    template <typename T>
    T getAttribute(conststr name, ID id) const
    {
        try
        {
            return attributes.at(name)->valueAt<float>(id);
        }
        catch (const std::exception &e)
        {
            std::invalid_argument(" Attribute " + name + " for node with name " + this->getNodeByID(id)->getName() + " doesn't exist");
        }
    }

    template <typename T>
    T getAttribute(conststr name, conststr nodeName) const
    {
        ID id = this->getNodeByName(nodeName)->getID();
        return getAttribute<T>(name, id);
    }

    friend class CarbonNetwork;
};

#endif
#include "node.h"

Node::Node()
{
    this->name = "";
    this->id = 0;
}

Node::Node(conststr name)
{
    this->name = name;
    this->id = 0;
}

Node::Node(conststr name, ID id)
{
    this->name = name;
    this->id = id;
}

void Node::setName(conststr name)
{
    this->name = name;
}

std::string Node::getName() const
{
    return this->name;
}

int Node::getID() const
{
    return this->id;
}

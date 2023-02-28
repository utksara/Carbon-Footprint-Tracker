#ifndef PROCESS_H
#define PROCESS_H

#include "item.h"

#define PROCESS "process"

class Process : public Node
{

private:
    static ID globalID;
    float footprint;
    std::vector<ID> products;

public:
    using Node::Node;
    Process(conststr name);
    std::string getType() const;
    float getFootPrint() const;
    std::vector<ID> getProducts() const;
    void addProduct(ID id);
    void setFootPrint(float footprint);
};

#endif
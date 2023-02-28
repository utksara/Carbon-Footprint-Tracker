#ifndef ITEM_H
#define ITEM_H

#include "node.h"
#include <vector>
#include <string>
#include <map>

#define ITEM "item"
class Item : public Node
{
    float footprint;
    static unsigned int globalID;
    std::map<std::shared_ptr<Node>, float> composition;

public:
    using Node::Node;
    explicit Item(conststr itemName, float footprint);
    Item(conststr itemName);
    void showMadeFrom();
    void showMadeInto();
    void setFootprint(float footprint);
    void setComposition(std::vector<std::pair<std::shared_ptr<Node>, float>> ingredientsAmount);
    float getFootPrint() const;
    std::string getType() const;
    void setComposition(std::shared_ptr<Node> ingredient, float quantity);
    float getComposition(std::shared_ptr<Node> ingredient) const;
};

#endif
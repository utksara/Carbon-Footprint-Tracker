#ifndef ITEM_GRAPH_H
#define ITEM_GRAPH_H

#include "graph.h"
#include "item.h"

class ItemGraph : public Graph
{
public:
    void addItem(std::shared_ptr<Item> item);
    void linkProductToIngredient(std::shared_ptr<Item> product, std::shared_ptr<Item> ingredient);
    void linkProductToIngredient(std::shared_ptr<Item> product, std::vector<std::string> ingredients);
    std::shared_ptr<Item> getAllItems(conststr itemname) const;
    std::shared_ptr<Item> getItemByName(conststr itemname) const;
    std::shared_ptr<Item> getItemByID(ID itemId) const;
    void showAllItems();
    float getTotalAttributeValueOfConnectedNodes(conststr attributeName, ID id, float quantity) const;
};
#endif
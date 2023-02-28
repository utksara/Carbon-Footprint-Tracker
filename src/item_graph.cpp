#include "item_graph.h"
#include <iostream>
#include "item.h"

void ItemGraph::addItem(std::shared_ptr<Item> item)
{
    this->addNode(item);
    this->addDefaultEdge(item->getID());
    std::cout << "\n"
              << "added item " << item->getName();
}

void ItemGraph::showAllItems()
{
    std::cout << "\n"
              << "list of items are";
    for (auto item : this->getNodes())
    {
        std::cout << "\n"
                  << item.second->getName();
    }

    std::cout << "\n";
}

std::shared_ptr<Item> ItemGraph::getItemByName(conststr itemname) const
{
    std::shared_ptr<Node> n = this->getNodeByName(itemname);
    return std::static_pointer_cast<Item>(n);
}

std::shared_ptr<Item> ItemGraph::getItemByID(const ID itemId) const
{
    std::shared_ptr<Node> n = this->getNodeByID(itemId);
    return std::static_pointer_cast<Item>(n);
}

void ItemGraph::linkProductToIngredient(std::shared_ptr<Item> product, std::shared_ptr<Item> ingredient)
{
    this->addEdge(product->getID(), ingredient->getID());
}

void ItemGraph::linkProductToIngredient(std::shared_ptr<Item> product, std::vector<std::string> ingredients)
{
    for (std::string itemName : ingredients)
    {
        std::shared_ptr<Item> item = std::static_pointer_cast<Item>(this->getNodeByName(itemName));
        if (item == nullptr)
        {
            std::string errorMessage = "item " + itemName + " doesn't exist";
            throw std::invalid_argument(errorMessage);
        }
        this->linkProductToIngredient(product, item);
    }
}

float ItemGraph::getTotalAttributeValueOfConnectedNodes(conststr attributeName, ID id, float quantity) const
{
    float total;
    if (this->getParentNodeIds(id).size() == 0)
    {
        return getAttribute<float>(attributeName, id) * quantity;
    }
    for (auto parentId : this->getParentNodeIds(id))
    {
        float parentQuantity = quantity * this->getItemByID(id)->getComposition(this->getNodeByID(parentId));
        total += parentQuantity * getTotalAttributeValueOfConnectedNodes(attributeName, parentId, parentQuantity);
    }
    return total;
}

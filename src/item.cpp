#include "item.h"
#include "node.h"
#include <iostream>

unsigned int Item::globalID = 0;

Item::Item(conststr itemName, float footprint) : Node(itemName, Item::globalID)
{
    if (globalID == MAX_ITEMS)
    {
        std::cout << "Max number of items reached! No more items can be created";
        return;
    }
    this->setFootprint(footprint);
    Item::globalID += 1;
}

Item::Item(conststr itemName) : Item(itemName, float(-1))
{
}

float Item::getFootPrint() const
{
    return this->footprint;
}

std::string Item::getType() const
{
    return ITEM;
}

void Item::setFootprint(float footprint)
{
    this->footprint = footprint;
}

void Item::setComposition(std::vector<std::pair<std::shared_ptr<Node>, float>> ingredientsAmount)
{
    for (auto ingredient : ingredientsAmount)
    {
        this->composition.insert(ingredient);
    }
}

void Item::setComposition(std::shared_ptr<Node> ingredient, float quantity)
{
    if (this->composition.find(ingredient) == this->composition.end())
    {
        this->composition.insert(std::pair<std::shared_ptr<Node>, float>(ingredient, quantity));
    }
    else
    {
        this->composition.at(ingredient) = quantity;
    }
}

float Item::getComposition(std::shared_ptr<Node> ingredient) const
{
    if (this->composition.find(ingredient) == this->composition.end())
    {
        return 0;
    }
    return this->composition.at(ingredient);
}
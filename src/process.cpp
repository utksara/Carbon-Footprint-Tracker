#include "process.h"

unsigned int Process::globalID = MAX_ITEMS + 1;

std::string Process::getType() const
{
    return PROCESS;
}

Process::Process(conststr name) : Node(name, Process::globalID)
{
    this->setFootPrint(0);
    Process::globalID += 1;
}

std::vector<ID> Process::getProducts() const
{
    return this->products;
}

void Process::addProduct(ID id)
{
    this->products.push_back(id);
}

void Process::setFootPrint(float footprint)
{
    if (footprint < 0)
    {
        throw std::invalid_argument("footprint value of a process cant be negative");
    }
    this->footprint = footprint;
}

float Process::getFootPrint() const
{
    return this->footprint;
}
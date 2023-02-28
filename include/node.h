#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <memory>

typedef unsigned int ID;
typedef const std::string &conststr;

#define MAX_ITEMS 1000
#define MAX_PROCESSES MAX_ITEMS *MAX_ITEMS
class Node
{
private:
    std::string name;
    ID id;

public:
    explicit Node();
    explicit Node(conststr name);
    explicit Node(conststr name, ID id);
    void setName(conststr name);
    std::string getName() const;
    int getID() const;
};

#endif
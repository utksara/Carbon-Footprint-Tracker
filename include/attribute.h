#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "node.h"
#include <map>
#include <functional>
#include <vector>

class Attribute
{
public:
    Attribute()
    {
    }

    template <typename T>
    T valueAt(ID id) const
    {
        return T(valueAtfloat(id));
    }

    virtual float valueAtfloat(ID id) const
    {
        return 0;
    }

    virtual void set(ID id, bool value)
    {
    }

    virtual void set(ID id, float value)
    {
    }

    virtual float reduce()
    {
        std::cout << "\ndefault called!";
        return 0;
    }

    virtual float reduce(std::vector<ID> ids)
    {
        return 0;
    }
};

#endif
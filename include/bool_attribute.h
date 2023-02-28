#include "attribute.h"

class BoolAttribute : public Attribute
{
private:
    std::map<ID, bool> boolMap;

public:
    BoolAttribute()
    {
    }

    float valueAtfloat(ID id) const
    {
        return boolMap.at(id);
    }

    void set(ID id, bool value)
    {
        auto itr = boolMap.find(id);
        if (itr != boolMap.end())
            itr->second = value;
    }

    void add(ID id, bool value)
    {
        boolMap.insert(std::pair<ID, bool>{id, value});
    }

    float reduce()
    {
        bool value = true;
        for (auto attribute : boolMap)
        {
            value = value & attribute.second;
        }
        return float(value);
    }
};
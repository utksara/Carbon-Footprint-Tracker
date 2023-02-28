#include "attribute.h"

class FloatAttribute : public Attribute
{
private:
    std::map<ID, float> floatMap;

public:
    FloatAttribute()
    {
    }

    void add(ID id, float value)
    {
        floatMap.insert(std::pair<ID, float>{id, value});
    }

    float valueAtfloat(ID id) const
    {
        return floatMap.at(id);
    }

    void set(ID id, float value)
    {
        auto itr = floatMap.find(id);
        if (itr != floatMap.end())
            itr->second = value;
    }

    float reduce()
    {
        float value = 0;
        for (auto attribute : floatMap)
        {
            value += attribute.second;
        }
        return value;
    }

    float reduce(std::vector<ID> subIds)
    {
        float value = 0;
        for (auto subId : subIds)
        {
            value += floatMap.at(subId);
        }
        return value;
    }
};
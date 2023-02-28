#define CARBON_NETWORK_H

#include "item_graph.h"
#include "item_process_graph.h"

enum class Objective
{
    minimization,
    maximization,
    constraint
};

class CarbonNetwork
{
private:
    std::string name;
    ItemGraph *itemGraph;
    ItemProcessGraph *itemProcessGraph;
    bool _addItem(conststr itemName);
    bool _addProcess(conststr processName);
    float _getFootPrint(conststr itemName, float quantity, bool save) const;

public:
    CarbonNetwork();
    CarbonNetwork(conststr name);
    CarbonNetwork(int n, float acccumulationFactor);
    float getFootPrint(conststr itemName, float quantity = 1, bool save = false) const;
    float getOptimalFootPrint(conststr itemName, float quantity = 1, bool showPathway = false) const;
    float getItemComposition(conststr itemName, conststr ingredientItemName) const;
    ID getItemId(conststr itemName) const;
    void addItem(conststr itemName);
    void addItem(conststr itemName, std::vector<std::string> madeFrom, std::vector<std::string> madeInto, std::vector<std::string> madeIn);
    void addProcess(conststr processName);
    void setMadeIn(conststr itemName, std::vector<std::string> madeIn);
    void setMadeIn(conststr itemName, conststr madeIn);
    void setMadeFrom(conststr itemName, std::vector<std::string> madeFrom);
    void setMadeFrom(conststr itemName, conststr madeFrom, float madeFromQuantity);
    void setMadeFrom(conststr itemName, conststr madeFrom);
    void setMadeFrom(conststr itemName, std::vector<std::pair<std::string, float>> madeFrom);
    void setMadeInto(conststr itemName, std::vector<std::string> madeInto);
    void setMadeInto(conststr itemName, conststr madeInto);
    void setMadeInto(conststr itemName, conststr madeInto, float madeIntoQuantity);
    void setFootprintforItem(conststr itemName, float footprint);
    void setFootprintforProcess(conststr processName, float footprint);
    void showAllItems();
    void showItemDetails(conststr name);
    void showProcessDetails(conststr name);
    void showAllProcessesforItem(conststr name);
    void showAttributeforAllItems(conststr name);
    void showOptimalFootPrintPathway(conststr itemName, float quantity);
    void addAttribute(conststr name, conststr nodetype, bool initialValue);
    void addAttribute(conststr name, conststr nodetype, float initialValue);
    void addAttribute(conststr name, conststr nodetype, float initialValue, TranformationFunction transformation);
    float getAttribute(conststr name, ID id, conststr nodeType) const;
    float getAttribute(conststr attributeName, conststr itemName, conststr nodeType) const;
    float getTotalAttributeValue(conststr attributeName, conststr nodeType) const;
    float getTotalAttributeValue(conststr attributeName, std::function<bool(float)> condition, conststr nodeType) const;
    void transformAttribute(conststr name, conststr nodetype, TranformationFunction transformation);
};

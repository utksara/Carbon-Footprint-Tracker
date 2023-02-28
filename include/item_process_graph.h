#ifndef ITEM_PROCESS_GRAPH_H
#define ITEM_PROCESS_GRAPH_H

#include "process.h"
#include "graph.h"

class ItemProcessGraph : public Graph
{
private:
    std::vector<ID> itemIds;
    std::vector<ID> processIds;

public:
    void addItem(std::shared_ptr<Item> item);
    void addProcess(std::shared_ptr<Process> process);
    std::shared_ptr<Process> getProcessByName(conststr itemname) const;
    void linkProductToProcess(std::shared_ptr<Item> item, std::shared_ptr<Process> processName);
    void linkProductToProcess(std::shared_ptr<Item> item, std::vector<std::string> processNames);
    float getAverageFootprintFromProcesses(std::shared_ptr<Item> item) const;
    float getMinimumFootprintFromProcesses(std::shared_ptr<Item> item, float quantity = 1, bool showPathway = false) const;
    bool hasProcess(conststr name) const;
    void showAllProcessesofItem(std::shared_ptr<Item> item);
    std::vector<ID> getAllProcessesofItem(std::shared_ptr<Item> item) const;
};
#endif
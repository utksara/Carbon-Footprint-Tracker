#include "item_process_graph.h"

void ItemProcessGraph::addItem(std::shared_ptr<Item> item)
{
    if (item->getType().compare(ITEM) == 0)
    {
        this->itemIds.push_back(item->getID());
        this->addDefaultEdge(item->getID());
        this->addNode(item);
    }
    else
    {
        throw std::invalid_argument("Should add item instead of any other node");
    }
}

void ItemProcessGraph::addProcess(std::shared_ptr<Process> process)
{
    if (process->getType().compare(PROCESS) == 0)
    {
        this->processIds.push_back(process->getID());
        this->addNode(process);
    }
    else
    {
        throw std::invalid_argument("Should add process instead of any other node");
    }
}

bool ItemProcessGraph::hasProcess(conststr name) const
{
    if (this->getNodeByName(name) == nullptr)
    {
        return false;
    }
    return true;
}

std::shared_ptr<Process> ItemProcessGraph::getProcessByName(conststr itemname) const
{
    if (!this->hasProcess(itemname))
    {
        std::cout << " Process with name " << itemname << " doesn't exist";
    }
    std::shared_ptr<Node> n = this->getNodeByName(itemname);
    return std::static_pointer_cast<Process>(n);
}

void ItemProcessGraph::linkProductToProcess(std::shared_ptr<Item> item, std::shared_ptr<Process> process)
{
    process->addProduct(item->getID());
    this->addEdge(item->getID(), process->getID());
}

void ItemProcessGraph::linkProductToProcess(std::shared_ptr<Item> item, std::vector<std::string> processNames)
{
    for (std::string processName : processNames)
    {
        std::shared_ptr<Process> process = this->getProcessByName(processName);
        if (process == nullptr)
        {
            std::string errorMessage = "Process " + processName + " doesn't exist";
            throw std::invalid_argument(errorMessage);
        }
        this->linkProductToProcess(item, process);
    }
}

void ItemProcessGraph::showAllProcessesofItem(std::shared_ptr<Item> item)
{
    for (ID processID : this->getEdgesAt(item->getID()))
    {
        std::cout << "\n"
                  << this->getNodeByID(processID)->getName();
    }
}

std::vector<ID> ItemProcessGraph::getAllProcessesofItem(std::shared_ptr<Item> item) const
{
    return this->getEdgesAt(item->getID());
}

float ItemProcessGraph::getAverageFootprintFromProcesses(std::shared_ptr<Item> item) const
{
    std::vector<ID> allProcessesforItem = this->getAllProcessesofItem(item);
    float averageFootprint = 0;
    int processCount = 0;
    for (ID processID : allProcessesforItem)
    {
        std::string processName = this->getNodeByID(processID)->getName();
        averageFootprint += this->getProcessByName(processName)->getFootPrint();
        processCount += 1;
    }

    if (processCount == 0)
    {
        return 0;
    }

    averageFootprint = averageFootprint / float(processCount);
    return averageFootprint;
}

float ItemProcessGraph::getMinimumFootprintFromProcesses(std::shared_ptr<Item> item, float quantity, bool showPathway) const
{
    std::vector<ID> allProcessesforItem = this->getAllProcessesofItem(item);
    float minimumFootprint = 0;
    bool initValueAssigned = false;
    std::string bestProcess;
    for (ID processID : allProcessesforItem)
    {
        std::string processName = this->getNodeByID(processID)->getName();
        if (!initValueAssigned)
        {
            minimumFootprint = quantity * this->getProcessByName(processName)->getFootPrint();
            initValueAssigned = true;
            bestProcess = processName;
        }
        if (minimumFootprint > quantity * this->getProcessByName(processName)->getFootPrint())
        {
            minimumFootprint = quantity * this->getProcessByName(processName)->getFootPrint();
            bestProcess = processName;
        }
    }
    if (showPathway)
        std::cout << bestProcess << "-->";
    return minimumFootprint;
}
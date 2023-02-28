#include "carbon_network.h"

/*Basic constructor*/
CarbonNetwork::CarbonNetwork()
{
    this->name = "";
    itemGraph = new ItemGraph();
    itemProcessGraph = new ItemProcessGraph();
}

/*Constructor which generates networks with total n items with each layer
containg 5 items (which means it takes 5 items to produce another 5 new
products). The accumulationFactor indicated if there is net consumpton in
an activity. Accumulation factor of 1 means net zero consumption and hihger than one
means net positive consumption*/
CarbonNetwork::CarbonNetwork(int n, float acccumulationFactor)
{
    if (n < 10)
    {
        std::cout << " number of items have to be atleast 10! running after setting n = 10";
        n = 10;
    }
    this->name = "";
    itemGraph = new ItemGraph();
    itemProcessGraph = new ItemProcessGraph();
    const std::string itemname = "item";
    for (int i = 1; i <= n; i++)
    {
        this->_addItem("item" + std::to_string(i));
    }
    int ingredientID{1};
    int productID = ingredientID + 5;

    for (int i = 1; i <= 5; i++)
    {
        float r = 5 * ((float)rand() / (RAND_MAX)) * ((float)rand() / (RAND_MAX));
        this->setFootprintforItem("item" + std::to_string(i), r);
    }

    int extraProductPerLayer = 0;
    while (productID < n)
    {
        for (int i = 0; i < 5; i++)
        {
            if (productID + i > n)
            {
                break;
            }
            float composition1 = ((float)rand() / (RAND_MAX));
            float composition2 = acccumulationFactor - composition1;
            this->setMadeFrom("item" + std::to_string(productID + i), "item" + std::to_string(ingredientID + i), composition1);
            this->setMadeFrom("item" + std::to_string(productID + i), "item" + std::to_string((ingredientID + (i + 2) % 5)), composition2);
        }
        ingredientID = productID;
        productID = productID + 5;
    }
}

/*Constructor with name*/
CarbonNetwork::CarbonNetwork(conststr name)
{
    this->name = name;
    itemGraph = new ItemGraph();
    itemProcessGraph = new ItemProcessGraph();
}

/*addItem no output*/
bool CarbonNetwork::_addItem(conststr itemName)
{
    if (!this->itemGraph->nodeExists(itemName))
    {
        std::shared_ptr<Item> newItem(new Item(itemName));
        this->itemGraph->addItem(newItem);
        this->itemProcessGraph->addItem(newItem);
        return true;
    }
    return false;
}

/*addItem with output*/
void CarbonNetwork::addItem(conststr itemName)
{
    if (!_addItem(itemName))
    {
        std::cout << "\n"
                  << "Item " << itemName << " already exists";
    }
}

float CarbonNetwork::getItemComposition(conststr itemName, conststr ingredientItemName) const
{
    std::shared_ptr<Node> ingredientItem = this->itemGraph->getItemByName(ingredientItemName);
    return this->itemGraph->getItemByName(itemName)->getComposition(ingredientItem);
}

bool CarbonNetwork::_addProcess(conststr processName)
{
    if (!this->itemProcessGraph->nodeExists(processName))
    {
        std::shared_ptr<Process> newProcess(new Process(processName));
        this->itemProcessGraph->addProcess(newProcess);
        return true;
    }
    return false;
}

void CarbonNetwork::addProcess(conststr processName)
{
    if (!_addProcess(processName))
    {
        std::cout << "\n"
                  << "Process " << processName << " already exists";
    }
}

void CarbonNetwork::addItem(conststr itemName, std::vector<std::string> madeFrom, std::vector<std::string> madeInto, std::vector<std::string> madeIn)
{
    for (conststr madefromitem : madeFrom)
    {
        this->setMadeFrom(itemName, madefromitem);
    }

    for (conststr madeintoitem : madeInto)
    {
        this->setMadeInto(itemName, madeintoitem);
    }

    for (conststr madeinProcess : madeIn)
    {
        this->setMadeIn(itemName, madeinProcess);
    }
}

void CarbonNetwork::showAllItems()
{
    itemGraph->showAllItems();
}

/*it takes give quantity of ingredient(madeFrom) to make given item(itemName)*/
void CarbonNetwork::setMadeFrom(conststr itemName, conststr madeFrom, float madeFromQuantity)
{
    _addItem(madeFrom);
    _addItem(itemName);
    std::shared_ptr<Item> product = this->itemGraph->getItemByName(itemName);
    std::shared_ptr<Item> ingredient = this->itemGraph->getItemByName(madeFrom);
    product->setComposition(ingredient, madeFromQuantity);
    this->itemGraph->linkProductToIngredient(product, ingredient);
}

void CarbonNetwork::setMadeFrom(conststr itemName, conststr madeFrom)
{
    this->setMadeFrom(itemName, madeFrom, 1);
}

/*Given item is made from all these ingedients(madefrom) with equal proportions*/
void CarbonNetwork::setMadeFrom(conststr itemName, std::vector<std::string> madeFrom)
{
    for (std::string ingredient : madeFrom)
    {
        setMadeFrom(itemName, ingredient);
    }
}

/*Given item is made from all these ingedients(madefrom) with equal wiht given quantities*/
void CarbonNetwork::setMadeFrom(conststr itemName, std::vector<std::pair<std::string, float>> madeFrom)
{
    for (std::pair<std::string, float> ingredient : madeFrom)
    {
        setMadeFrom(itemName, ingredient.first, ingredient.second);
    }
}

/*it takes given quantity of ingredient(itemName) to make given item(madeInto) with given quantity (madeIntoQuantity)*/
void CarbonNetwork::setMadeInto(conststr itemName, conststr madeInto, float madeIntoQuantity)
{
    _addItem(itemName);
    _addItem(madeInto);
    std::shared_ptr<Item> ingredient = this->itemGraph->getItemByName(itemName);
    std::shared_ptr<Item> product = this->itemGraph->getItemByName(madeInto);
    product->setComposition(ingredient, float(1 / madeIntoQuantity));
    this->itemGraph->linkProductToIngredient(product, ingredient);
}

void CarbonNetwork::setMadeInto(conststr itemName, conststr madeInto)
{
    this->setMadeInto(itemName, madeInto, 1);
}

void CarbonNetwork::setMadeInto(conststr itemName, std::vector<std::string> madeInto)
{
    for (std::string product : madeInto)
    {
        setMadeInto(product, itemName);
    }
}

/*Calculates minimum footprint one can have to get given quantity of an item
If show pathway is set true, it will show the list of processes it takes
to get optimal footprint*/
float CarbonNetwork::getOptimalFootPrint(conststr itemName, float quantity, bool showPathway) const
{
    std::shared_ptr<Item> item = this->itemGraph->getItemByName(itemName);
    if (item->getFootPrint() > -1)
    {
        return quantity * item->getFootPrint();
    }
    float totalFootprint = this->itemProcessGraph->getMinimumFootprintFromProcesses(item, quantity, showPathway);
    for (ID parentItemID : this->itemGraph->getEdgesAt(item->getID()))
    {
        std::shared_ptr<Item> parentItem = this->itemGraph->getItemByID(parentItemID);
        totalFootprint += this->getOptimalFootPrint(parentItem->getName(), item->getComposition(parentItem) * quantity, showPathway);
    }
    return totalFootprint;
}

/*Shows the list of processes it takes to get optimal footprint*/
void CarbonNetwork::showOptimalFootPrintPathway(conststr itemName, float quantity)
{
    std::cout << "\nOptimal pathway to obtain " << quantity << " units of " << itemName << " : ";
    this->getOptimalFootPrint(itemName, quantity, true);
}

/*Average footprint (assuming an item is obtained from all possible processes in equal proportions)*/
float CarbonNetwork::getFootPrint(conststr itemName, float quantity, bool save) const
{
    float footprint = _getFootPrint(itemName, quantity, save);
    if (this->itemGraph->hasAttribute("tempfootprint"))
    {
        this->itemGraph->removeAttribute("tempfootprint");
    }
    return footprint;
}

float CarbonNetwork::_getFootPrint(conststr itemName, float quantity, bool save) const
{
    if (!this->itemGraph->hasAttribute("tempfootprint"))
    {
        this->itemGraph->addAttribute("tempfootprint", float(-1));
    }
    std::shared_ptr<Item> item = this->itemGraph->getItemByName(itemName);

    if (item->getFootPrint() > -1)
    {
        return quantity * item->getFootPrint();
    }

    if (this->itemGraph->getAttribute<float>("tempfootprint", item->getID()) > -1)
    {
        std::cout<<"\n\nyes";
        return quantity * this->itemGraph->getAttribute<float>("tempfootprint", item->getID());
    }

    float totalFootprintPerItem = this->itemProcessGraph->getAverageFootprintFromProcesses(item);
    for (ID parentItemID : this->itemGraph->getEdgesAt(item->getID()))
    {
        std::shared_ptr<Item> parentItem = this->itemGraph->getItemByID(parentItemID);
        totalFootprintPerItem += this->_getFootPrint(parentItem->getName(), item->getComposition(parentItem), save);
    }

    this->itemGraph->setAttribute("tempfootprint", item->getID(), totalFootprintPerItem);
    if (save)
    {
        item->setFootprint(totalFootprintPerItem);
    }
    return quantity * totalFootprintPerItem;
}

/*Set footprint of an item, (if it known already without calculation)*/
void CarbonNetwork::setFootprintforItem(conststr itemName, float footprint)
{
    this->itemGraph->getItemByName(itemName)->setFootprint(footprint);
}

/*Set footprint of a process*/
void CarbonNetwork::setFootprintforProcess(conststr processName, float footprint)
{
    this->itemProcessGraph->getProcessByName(processName)->setFootPrint(footprint);
}

ID CarbonNetwork::getItemId(conststr itemName) const
{
    std::shared_ptr<Item> item = this->itemGraph->getItemByName(itemName);
    return item->getID();
}

void CarbonNetwork::showProcessDetails(conststr name)
{
    std::shared_ptr<Process> process = this->itemProcessGraph->getProcessByName(name);
    if (process == nullptr)
    {
        std::cout << "Process with name " << name << " not found";
        return;
    }
    ID processID = process->getID();
    std::cout << "\n{";
    std::cout << "\n    Name : " << name;
    std::cout << "\n    ID : " << processID;
    std::cout << "\n    Footprint : ";
    if (process->getFootPrint() == 0)
    {
        std::cout << "Unset";
    }
    else
    {
        std::cout << process->getFootPrint();
    }
    std::cout << "\n    Produces : [";
    for (ID productID : process->getProducts())
    {
        std::cout << itemGraph->getNodeByID(productID)->getName() << ", ";
    }
    std::cout << "]";
    std::cout << "\n}";
    std::cout << "\n";
}

void CarbonNetwork::showItemDetails(conststr name)
{
    std::shared_ptr<Item> item = this->itemGraph->getItemByName(name);
    if (item == nullptr)
    {
        std::cout << "Item with name " << name << " not found";
        return;
    }
    ID itemID = item->getID();
    std::cout << "\n{";
    std::cout << "\n    Name : " << name;
    std::cout << "\n    ID : " << itemID;
    std::cout << "\n    Footprint : ";
    if (item->getFootPrint() == -1)
    {
        std::cout << "Uncalcualted";
    }
    else
    {
        std::cout << item->getFootPrint();
    }
    std::cout << "\n    Made from : [";
    for (ID parentID : itemGraph->getEdgesAt(itemID))
    {
        std::string parentName = itemGraph->getNodeByID(parentID)->getName();
        std::cout << parentName << " : " << this->getItemComposition(name, parentName) << " per unit , ";
    }
    std::cout << "]";
    std::cout << "\n}";
    std::cout << "\n";
}

/*show all the processes from which given item can be obtained*/
void CarbonNetwork::showAllProcessesforItem(conststr name)
{
    std::cout << "\n"
              << "The process making " << name << " are -";
    this->itemProcessGraph->showAllProcessesofItem(std::static_pointer_cast<Item>(this->itemGraph->getNodeByName(name)));
    std::cout << "\n";
}

void CarbonNetwork::setMadeIn(conststr itemName, std::vector<std::string> madeIn)
{
    for (std::string processName : madeIn)
    {
        this->setMadeIn(itemName, processName);
    }
}

void CarbonNetwork::setMadeIn(conststr itemName, conststr madeIn)
{
    this->_addItem(itemName);
    this->_addProcess(madeIn);
    std::shared_ptr<Item> item = this->itemGraph->getItemByName(itemName);
    std::shared_ptr<Process> process = this->itemProcessGraph->getProcessByName(madeIn);
    this->itemProcessGraph->linkProductToProcess(item, process);
}

/*adds attribute (user defined quantity)*/
void CarbonNetwork::addAttribute(conststr name, conststr nodetype, float initialValue)
{
    if (nodetype.compare(ITEM) == 0)
    {
        this->itemGraph->addAttribute(name, initialValue);
    }
    else if (nodetype.compare(PROCESS) == 0)
    {
        this->itemProcessGraph->addAttribute(name, initialValue);
    }
    else if (nodetype.compare("all") == 0)
    {
        this->itemGraph->addAttribute(name, initialValue);
        this->itemProcessGraph->addAttribute(name, itemGraph->attributes.at(name));
    }
}

void CarbonNetwork::addAttribute(conststr name, conststr nodetype, float initialValue, TranformationFunction transformation)
{
    if (this->itemGraph->hasAttribute(name))
    {
        std::cout << " attribute " << name << " already exists ";
        return;
    }
    addAttribute(name, nodetype, initialValue);
    this->itemGraph->mapAttribute(name, transformation);
}

void CarbonNetwork::addAttribute(conststr name, conststr nodetype, bool initialValue)
{
    this->itemGraph->addAttribute(name, initialValue);
}

/*get value of attribute if it was added already*/
float CarbonNetwork::getAttribute(conststr name, ID id, conststr nodeType) const
{
    return this->itemGraph->getAttribute<float>(name, id);
}

float CarbonNetwork::getAttribute(conststr attributeName, conststr nodeName, conststr nodeType) const
{
    if (nodeType.compare(ITEM) == 0)
        return this->itemGraph->getAttribute<float>(attributeName, this->itemGraph->getItemByName(nodeName)->getID());
    if (nodeType.compare(PROCESS) == 0)
        return this->itemProcessGraph->getAttribute<float>(attributeName, this->itemProcessGraph->getProcessByName(nodeName)->getID());
}

void CarbonNetwork::showAttributeforAllItems(conststr name)
{
    std::cout << "\n " << name;
    for (auto nodemap : this->itemGraph->getNodes())
    {
        std::shared_ptr<Node> node = nodemap.second;
        ID id = nodemap.first;
        std::cout << "\n " << id << "("
                  << " " << node->getName() << " ) : " << getAttribute(name, id, ITEM);
    }
}

float CarbonNetwork::getTotalAttributeValue(conststr attributeName, conststr nodeType) const
{
    if (nodeType.compare(ITEM) == 0)
        return this->itemGraph->reduce(attributeName);
    if (nodeType.compare(PROCESS) == 0)
        return this->itemProcessGraph->reduce(attributeName);
}

float CarbonNetwork::getTotalAttributeValue(conststr attributeName, std::function<bool(float)> condition, conststr nodeType) const
{
    std::vector<ID> filteredIds;
    for (auto node : this->itemGraph->getNodes())
    {
        ID id = node.first;
        if (condition(getAttribute(attributeName, id, nodeType)))
        {
            filteredIds.push_back(id);
        }
    }
    return this->itemGraph->reduce(attributeName, filteredIds);
}

/*functional way to tranform attribute, useful for relational quanitities
Example: If there is an attribute "cost", its value will include values of all
parent items and production as well (very much like footprint)*/
void CarbonNetwork::transformAttribute(conststr name, conststr nodetype, TranformationFunction transformation)
{
    if (!this->itemGraph->hasAttribute(name) && nodetype.compare(ITEM) == 0)
    {
        std::cout << " attribute " << name << " doesn't exists for items";
        return;
    }
    if ((!this->itemProcessGraph->hasAttribute(name)) && (nodetype.compare(PROCESS) == 0))
    {
        std::cout << " attribute " << name << " doesn't exists  for processes";
        return;
    }
    if (nodetype.compare(ITEM) == 0)
    {
        this->itemGraph->mapAttribute(name, transformation);
    }
    if (nodetype.compare(PROCESS) == 0)
    {
        this->itemProcessGraph->mapAttribute(name, transformation);
    }
}

#include "carbon_network.h"


int main()
{
    CarbonNetwork carbonNetwork("database1");

    std::cout << "\n\n"
              << "-----";
    std::cout << "\n"
              << "Demos";
    std::cout << "\n"
              << "-----";

    /* Demo 1*/
    std::cout << "\n"
              << "1. Demo to show addition of items";
    std::cout << "\n"
              << "----------------";
    carbonNetwork.addItem(
        "bread",
        {"flour", "yeast"},
        {"pizza", "donut"},
        {"bakery"});
    carbonNetwork.showAllItems();

    /* Demo 2*/
    std::cout << "\n"
              << "2. Demo to show item ids";
    std::cout << "\n"
              << "----------------";
    std::string bread = "bread";
    std::string flour = "flour";
    std::string pizza = "pizza";
    std::cout << "\n"
              << "The id of " << bread << " is " << carbonNetwork.getItemId(bread);
    std::cout << "\n"
              << "The id of " << flour << " is " << carbonNetwork.getItemId(flour);
    std::cout << "\n"
              << "The id of " << pizza << " is " << carbonNetwork.getItemId(pizza);

    /* Demo 3*/
    std::cout << "\n\n"
              << "3. Demo of showing item details";
    std::cout << "\n"
              << "----------------";
    std::string wheat = "wheat";
    carbonNetwork.setMadeFrom(flour, wheat, 0.5);
    carbonNetwork.showItemDetails(bread);
    carbonNetwork.showItemDetails(flour);

    /* Demo 4*/
    std::cout << "\n\n"
              << "4. Demo of showing process details";
    std::cout << "\n"
              << "----------------";
    std::string yeast = "yeast";
    std::string bakery = "bakery";
    std::string windmill = "windmill";
    std::string regularMill = "regualrMill";
    carbonNetwork.addProcess(windmill);
    carbonNetwork.addProcess(regularMill);
    carbonNetwork.setMadeIn(flour, {windmill, regularMill});
    carbonNetwork.showProcessDetails(bakery);
    carbonNetwork.showProcessDetails(windmill);

    /* Demo 5*/
    std::cout << "\n"
              << "5. Demo showing all process that make an item";
    std::cout << "\n"
              << "----------------";
    carbonNetwork.showAllProcessesforItem(flour);

    /* Demo 6*/
    std::cout << "\n"
              << "6. Demo showing calculation of average footprint";
    std::cout << "\n"
              << "----------------";
    carbonNetwork.setFootprintforProcess(windmill, 7);
    carbonNetwork.setFootprintforProcess(regularMill, 20);
    carbonNetwork.setFootprintforItem(wheat, 5);
    carbonNetwork.setFootprintforItem(yeast, 7);
    carbonNetwork.setFootprintforProcess(bakery, 10);
    std::cout << "\n"
              << "The footprint of " << flour << " is " << carbonNetwork.getFootPrint(flour);
    std::cout << "\n"
              << "The footprint of two " << bread << " is " << carbonNetwork.getFootPrint(bread, 2);

    /* Demo 7*/
    std::cout << "\n"
              << "\n Demonstrating addition of attribute costs to the items such that \n cost of ingredient is added to the product: ";
    std::cout << "\n"
              << "---------------------------------------------------------------------";
    std::cout << "\nList of all costs ";
    carbonNetwork.addAttribute("cost", ITEM, float(7.5), [carbonNetwork](float currentvalue, conststr productName, conststr ingredientName)
                               { return currentvalue + carbonNetwork.getItemComposition(productName, ingredientName) * carbonNetwork.getAttribute("cost", ingredientName, "item"); });
    carbonNetwork.showAttributeforAllItems("cost");
    std::cout << "\nTotal cost"
              << " : ";
    std::cout << carbonNetwork.getTotalAttributeValue("cost", "item");

    /* Demo 8*/
    std::cout << "\n"
              << "\n Demonstrating calculation of total costs of items costing \n less than 8 and items more than or equals to 30";
    std::cout << "\n"
              << "---------------------------------------------------------------------";
    std::cout << "\nTotal cost of items less than 8"
              << " : ";
    std::cout << carbonNetwork.getTotalAttributeValue(
        "cost", [](float x)
        { return x < 8; },
        "item");
    std::cout << "\nTotal cost of items more than or equals to 30"
              << " : ";
    std::cout << carbonNetwork.getTotalAttributeValue(
        "cost", [](float x)
        { return x >= 30; },
        "item");

    /* Demo 9*/
    std::cout << "\n"
              << "\nDemonstrating calculation of average footpring and optimal footprint\n (with least possible value) for given quantity of item";
    std::cout << "\n"
              << "---------------------------------------------------------------------";
    std::cout << "\n"
              << "Average footprint for two units of bread : ";
    std::cout << carbonNetwork.getFootPrint(bread, 2);
    std::cout << "\n"
              << "Optimal footprint for two units of bread : ";
    std::cout << carbonNetwork.getOptimalFootPrint(bread, 2);
    carbonNetwork.showOptimalFootPrintPathway(bread, 2);
}
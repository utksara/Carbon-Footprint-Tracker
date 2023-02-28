#include <gtest/gtest.h>
#include "carbon_network.h"



TEST(CarbonNetworkTest, alltests) {    
    CarbonNetwork carbonNetwork;
    std::string bread = "bread";
    std::string flour = "flour";
    std::string pizza = "pizza";
    std::string wheat = "wheat";
    std::string yeast = "yeast";
    std::string bakery = "bakery";
    std::string windmill = "windmill";
    std::string regularMill = "regualrMill";
    carbonNetwork.addItem(
        "bread", 
        {"flour", "yeast"}, 
        {"pizza", "donut"}, 
        {"bakery"}
    );
    auto breadId = carbonNetwork.getItemId(bread);
    auto flourId = carbonNetwork.getItemId(flour);
    auto pizzaId = carbonNetwork.getItemId(pizza);
    EXPECT_EQ(breadId, 1);
    EXPECT_EQ(flourId, 0);
    EXPECT_EQ(pizzaId, 3);

    carbonNetwork.setMadeFrom(flour, wheat, 0.5);
    carbonNetwork.addProcess(windmill);
    carbonNetwork.addProcess(regularMill);
    carbonNetwork.setMadeIn(flour, {windmill, regularMill});

    carbonNetwork.setFootprintforProcess(windmill, 7);
    carbonNetwork.setFootprintforProcess(regularMill, 20);
    carbonNetwork.setFootprintforItem(wheat , 5);
    carbonNetwork.setFootprintforItem(yeast , 7);
    carbonNetwork.setFootprintforProcess(bakery, 10);
    auto footprintFlour = carbonNetwork.getFootPrint(flour);
    auto footprintBread = carbonNetwork.getFootPrint(bread,2);

    EXPECT_EQ(footprintFlour, 16);
    EXPECT_EQ(footprintBread, 66);

    carbonNetwork.addAttribute("cost", ITEM, float(7.5), [carbonNetwork](float currentvalue, conststr productName, conststr ingredientName){
    return currentvalue + carbonNetwork.getItemComposition(productName, ingredientName) * carbonNetwork.getAttribute("cost", ingredientName, "item");
    });

    auto totalCost = carbonNetwork.getTotalAttributeValue("cost", "item");
    EXPECT_EQ(totalCost, 120);

    auto costLess8 = carbonNetwork.getTotalAttributeValue("cost", [](float x) {return x < 8;}, "item");
    auto costMore30 = carbonNetwork.getTotalAttributeValue("cost", [](float x) {return x >= 30;}, "item");
    EXPECT_EQ(costLess8, 15);
    EXPECT_EQ(costMore30, 67.5); 

    auto ave_footprint_bread = carbonNetwork.getFootPrint(bread, 2);
    auto opt_footprint_bread = carbonNetwork.getOptimalFootPrint(bread, 2);

    EXPECT_EQ(ave_footprint_bread, 66);
    EXPECT_EQ(opt_footprint_bread, 53);

}





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

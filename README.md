# Carbon_footprint

## How to run
```
    mkdir build
    cd build
    cmake ..
    make
```
- If you want to have a virtual test yourself,  run `./alltests`

## How this works
- In any CPP file, first include  "carbon_network.h"
- In main function, create instance of CarbonNetwork class
- all the operations can be performed on this single instance


## Sample program
```
    #include "carbon_network.h"
int main() {

    CarbonNetwork carbonNetwork("database1");

    /*
        Item being added : "bread"
        Ingredients of the item: {"flour", "yeast"}
        Products of the item : {"pizza", "donut"}
        Processes that make this item : {"bakery"}
    */
    carbonNetwork.addItem(
                            "bread", 
                            {"flour", "yeast"}, 
                            {"pizza", "donut"}, 
                            {"bakery"}
                        );
    carbonNetwork.showAllItems(); // show all the items added
    carbonNetwork.setMadeFrom("flour", "wheat"); // setting the ingredients for flour
    carbonNetwork.showItemDetails("bread");// showing item details of bread

    carbonNetwork.addProcess("windmill"); // adding new process windmill
    carbonNetwork.addProcess("regularMill"); 
    carbonNetwork.setMadeIn("flour", {"windmill", "regularMill"}); // setting processes which can make flour

    carbonNetwork.setFootprintforProcess("windmill", 7); // setting footprint value for windmill
    carbonNetwork.setFootprintforProcess("regularMill", 20);
    carbonNetwork.setFootprintforItem("wheat" , 5);
    carbonNetwork.setFootprintforItem("yeast" , 7);
    carbonNetwork.setFootprintforProcess("bakery", 10);
    std::cout << carbonNetwork.getFootPrint("bread") // displaying footprint value of bread
```


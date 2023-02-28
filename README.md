# Carbon_footprint

## Whats new in version 3

- added comments in the user level functions to explain their purpose
- used smart pointers instead of regular pointers
- created function to generate semi-random carbon network with given paremeters to study performance
- modified gootprint calculation function by using caching to make it faster
- made changes in function to add attribute so that both item graph and item process graph can share same attribute values for items

- add GoogleTest framework
(Note: if it doesn't work then just comment every line with gtest in CMakeLists.txt and
just run '''cmake ./''' like before)

cmake -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg DCMAKE_SHARED_LINKER_FLAGS=-pg ./

## Whats new in version 2

### Things that were resolved from previous review
- Using cmake to build files
- CLI option available to
- Changes made in coding practices suggested in version1
### Things that are added
-A design pattern which allows interaction between various items and processes and makes the application scalable is chosen and implemented

- Ability to add/remove new attributes in the activities
- Implementation of graph algorithms, map-reduce, filter which will allow users to perform several queries in the network of activities
- The user can calculate footprint for given quantity of an item
- The user can get pathway of processes with minimum carbon footprint for a given item (for the cases where an item which can be obtained through multiple ways)

### Things that remaining to be done
Following task we were unable to complete in the given timeframe.
- using autotests to validate the functions
- getting the optimal footprint based on constraints (like cost/availability)
- getting intermediate item/process contributing maximum to the overall footprint 

## How to run
```
    mkdir build
    cd build
    cmake ..
    make
```
- If you want use GoogleTest for test,  run `./gtest`
- If you want to have a virtual test yourself,  run `./alltests`
- If you want to have a test about CLI, please refer to the part *[How to test CLI](# How to test CLI)*

## How this works
- In any CPP file, first include  "carbon_network.h"
- In main function, create instance of CarbonNetwork class
- all the operations can be performed on this single instance

## How to test CLI
Since no suitable third-party library was found, we are sorry that we can only provide some simple cli commands, you can refer to the following script to test. They have relatively strict syntax rules, which means you can't swap the order of the parameters at will.

First in command line run `make cli_demo` and then `./cli_demo`. It is recommended that you test the cli functions in the following order (with copy and pasting, as the current version does not have any error tolerance, any spelling mistakes will cause errors :) ).  

Commands start with `add/set` or end with * are **required** to be executed for the rest of the test code to be error-free. 



- `addItem -name <itemname> -madeFrom <item1> <item2> -madeInto <item1> <item2> -madeIn <item1> <item2>` *
```
addItem -name bread -madeFrom flour yeast -madeInto pizza donut -madeIn bakery
```

- `getItemId -name <itemname>`
```
getItemId -name bread
```
```
getItemId -name flour
```

- `setItemMadeFrom -name <itemname> -madeFrom <item1> -madeFromQuantity <quantity>` *
```
setItemMadeFrom -name flour -madeFrom wheat -madeFromQuantity 2
```

- `showItemDetails -name <itemname>`
```
showItemDetails -name bread
```
```
showItemDetails -name flour
```

- `addProcess -name <processname>` *
```
addProcess -name windmill
```
```
addProcess -name regularMill
```

- `setMadeIn -name <itemname> -madeIn <item1> <item2> ...` *
```
setMadeIn -name flour -madeIn windmill regularMill
```

- `showProcessDetails -name <processname>`
```
showProcessDetails -name bakery
```
```
showProcessDetails -name windmill
```
- `showAllProcessesforItem -name <itemname>` 
```
showAllProcessesforItem -name flour
```

- `setFootprintforProcess -name <processname> -footprint <footprint>` *
```
setFootprintforProcess -name windmill -footprint 7
```
```
setFootprintforProcess -name regularMill -footprint 20
```
```
setFootprintforProcess -name bakery -footprint 30
```

- `setFootprintforItem -name <itemname> -footprint <footprint>` *
```
setFootprintforItem -name wheat -footprint 5
```
```
setFootprintforItem -name yeast -footprint 7
```

- `getFootPrint -name <itemname>`
```
getFootPrint -name flour
```
```
getFootPrint -name bread
```


## Sample program
```
    #include "carbon_network.h"
int main() {

    CarbonNetwork *carbonNetwork = new CarbonNetwork();

    /*
        Item being added : "bread"
        Ingredients of the item: {"flour", "yeast"}
        Products of the item : {"pizza", "donut"}
        Processes that make this item : {"bakery"}
    */
    carbonNetwork->addItem(
                            "bread", 
                            {"flour", "yeast"}, 
                            {"pizza", "donut"}, 
                            {"bakery"}
                        );
    carbonNetwork->showAllItems(); // show all the items added
    carbonNetwork->setMadeFrom("flour", "wheat"); // setting the ingredients for flour
    carbonNetwork->showItemDetails("bread");// showing item details of bread

    carbonNetwork->addProcess("windmill"); // adding new process windmill
    carbonNetwork->addProcess("regularMill"); 
    carbonNetwork->setMadeIn("flour", {"windmill", "regularMill"}); // setting processes which can make flour

    carbonNetwork->setFootprintforProcess("windmill", 7); // setting footprint value for windmill
    carbonNetwork->setFootprintforProcess("regularMill", 20);
    carbonNetwork->setFootprintforItem("wheat" , 5);
    carbonNetwork->setFootprintforItem("yeast" , 7);
    carbonNetwork->setFootprintforProcess("bakery", 10);
    std::cout << carbonNetwork->getFootPrint("bread") // displaying footprint value of bread
```


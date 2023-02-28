#include "carbon_network.h"
#include <sstream>

void performCommand(std::vector<std::string> commands,CarbonNetwork *carbonNetwork){
   if(commands[0] == "addDatabase"){
        try
        {
            // CarbonNetwork *carbonNetwork = new CarbonNetwork();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    //addItem -name <itemname> -madeFrom <item1> <item2> -madeInto <item1> <item2> -madeIn <item1> <item2>
    else if(commands[0] == "addItem"){
        try
        {   
            std::vector<std::string> madeFrom, madeInto, madeIn;
            for(int i = 3; i < commands.size(); i++){
                if(commands[i] == "-madeFrom"){
                    for(int j = i+1; j < commands.size(); j++){
                        if(commands[j] == "-madeInto"){
                            break;
                        }
                        madeFrom.push_back(commands[j]);
                    }
                }
                else if(commands[i] == "-madeInto"){
                    for(int j = i+1; j < commands.size(); j++){
                        if(commands[j] == "-madeIn"){
                            break;
                        }
                        madeInto.push_back(commands[j]);
                    }
                }
                else if(commands[i] == "-madeIn"){
                    for(int j = i+1; j < commands.size(); j++){
                        madeIn.push_back(commands[j]);
                    }
                }
            }
            carbonNetwork->addItem(
                            commands[2], 
                            madeFrom, 
                            madeInto, 
                            madeIn
                        );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: addItem -name <itemname> -madeFrom <item1> <item2> -madeInto <item1> <item2> -madeIn <item1> <item2>" << std::endl;
        }
        
        
    }
    //getItemId -name <itemname>
    else if(commands[0] == "getItemId"){
         try
         {
             std::cout<< "\n" <<  "The id of "<< commands[2] << " is "<<carbonNetwork->getItemId(commands[2]) << "\n" ;
         }
         catch(const std::exception& e)
         {
            std::cerr << e.what() << '\n';
         }
         
    }

    //setItemMadeFrom -name <itemname> -madeFrom <item1> -madeFromQuantity <quantity>
    else if(commands[0] == "setItemMadeFrom"){
       try
       {
        float quantity = std::stof(commands[6]);
        carbonNetwork->setMadeFrom(commands[2], commands[4], quantity);
       }
       catch(const std::exception& e)
       {
        std::cerr << e.what() << '\n';
        std::cout << "Usage: setMadeFrom -name <itemname> -madeFrom <item1> -madeFromQuantity <quantity>" << std::endl;
       }
       
    }

    //showItemDetails -name <itemname>
    else if(commands[0] == "showItemDetails"){
        try
        {
           carbonNetwork->showItemDetails(commands[2]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: showItemDetails -name <itemname>" << std::endl;
        }
        
    }

    //addProcess -name <processname>
    else if(commands[0] == "addProcess"){
        try
        {
            carbonNetwork->addProcess(commands[2]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: addProcess -name <processname>" << std::endl;
        }  
    }

    //setMadeIn -name <itemname> -madeIn <item1> <item2> ...
    else if(commands[0] == "setMadeIn"){
        try
        {
            std::vector<std::string> madeIn;
            for(int i = 4; i < commands.size(); i++){
                madeIn.push_back(commands[i]);
            }
            carbonNetwork->setMadeIn(commands[2], madeIn);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: setMadeIn -name <itemname> -madeIn <item1> <item2> ..." << std::endl;
        }
        
    }

    //showProcessDetails -name <processname>
    else if(commands[0] == "showProcessDetails"){
        try
        {
            carbonNetwork->showProcessDetails(commands[2]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: showProcessDetails -name <processname>" << std::endl;
        }
    }

    //showAllProcessesforItem -name <itemname>
    else if(commands[0] == "showAllProcessesforItem"){
        try
        {
            carbonNetwork->showAllProcessesforItem(commands[2]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: showAllProcessesforItem -name <itemname>" << std::endl;
        }
    }

    //setFootprintforProcess -name <processname> -footprint <footprint>
    else if(commands[0] == "setFootprintforProcess"){
        try
        {
            float footprint = std::stof(commands[4]);
            carbonNetwork->setFootprintforProcess(commands[2], footprint);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: setFootprintforProcess -name <processname> -footprint <footprint>" << std::endl;
        }
    }

    //setFootprintforItem -name <itemname> -footprint <footprint>
    else if(commands[0] == "setFootprintforItem"){
        try
        {
            float footprint = std::stof(commands[4]);
            carbonNetwork->setFootprintforItem(commands[2], footprint);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: setFootprintforItem -name <itemname> -footprint <footprint>" << std::endl;
        }
    }

    //getFootPrint -name <itemname>
    else if(commands[0] == "getFootPrint"){
        try
        {
            std::cout << "\n" << "The footprint of " << commands[2] << " is " << carbonNetwork->getFootPrint(commands[2]) << "\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Usage: getFootPrint -name <itemname>" << std::endl;
        }
    }

    else{
        std::cout << "Invalid command" << std::endl;
    }
}

int main(){
    std::cout << "Welcome to Carbon Footprint Tracker. Please refer to the README file for instructions." << std::endl;
    //instantiating the carbon network
    CarbonNetwork *carbonNetwork = new CarbonNetwork("Carbon Network");

    while (true){

        std::cout << "\nPlease enter the command: (Enter 'exit' to exit the program)"<< std::endl;
        std::string command_line;
        std::getline(std::cin, command_line);
        if(command_line == "exit"){
        std::cout << "Exiting the program" << std::endl;
        break;
        }

        std::istringstream iss(command_line);
        std::vector<std::string> commands;
        std::string command;
        while (iss >> command){
            commands.push_back(command);
        } 

        performCommand(commands, carbonNetwork);
    }
    return 0;
}
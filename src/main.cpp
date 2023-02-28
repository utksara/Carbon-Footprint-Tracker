
#include "carbon_network.h"

int main()
{

    /*this program is used mainly to demonstrate working capacity of the application using
    its full capacity (by using max number of items) and testing performance*/

    /*total number of items*/
    int N = 1000;
    std::string max_item = std::to_string(N);

    /*higly sensitive paramters, keep it just above one*/
    float acccumulationFactor = 1.01;

    /*generating carbon network with given size*/
    CarbonNetwork carbonNetwork(N, acccumulationFactor);

    carbonNetwork.showItemDetails("item6");
    carbonNetwork.showItemDetails("item1");
    carbonNetwork.showItemDetails("item3");
    // carbonNetwork.setMadeFrom("item995", "item420");
    carbonNetwork.getFootPrint("item" + max_item, 1, false);
    carbonNetwork.showItemDetails("item" + max_item);
}
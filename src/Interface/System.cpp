// ****************************************************************************************************
// ****************************************** SYSTEM_CPP__ ********************************************
// ****************************************************************************************************

#include "System.h"
#include <string>
#include <iostream>
#include <regex>

using namespace std;

void System::clearScreen() {
    cout << string(50, '\n');
};


System::System() {

    controller = Controller();

    Menu baseMenu = Menu(controller);
    baseMenu.setMainOps({"Staff Optimizing", "Profit Optimizing", "Express Deliveries"});

    while(true) {
        string orderOption = baseMenu.intInputMenu("Hello! Please select an order to process!");
        while(!controller.readOrders(stoi(orderOption)))
            orderOption = baseMenu.intInputMenu("Hello! Please select an order to process!", "This order does not exists!");
        int sceneryOption = baseMenu.printOptionsMenu(baseMenu.getMainOps(), "Please select a way to process your order");

        if(sceneryOption == 2){
            vector<Order> ordersVec = controller.scenery3();
            baseMenu.anyInputMenu(getPrintableScenery3(ordersVec));
        }

        if (orderOption == "x") break;
    }
}

string System::getPrintableScenery3(const std::vector<Order>& orders) {
    string ret = "Here are the Orders, by ID, arranged for delivery:\n";
    for(auto o : orders){
        ret += "  -" + to_string(o.getId()) + "\n";
    }
    return ret;
}



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

        if (orderOption == "x") break;
    }
}

string System::fixString(string str) {
    size_t index = 0;
    while (true) {
        index = str.find("├", index);
        if (index == std::string::npos) break;
        cout<<"hey\n";
        str.replace(index, 1, "E");

        index += 1;
    }
    str = regex_replace(str, regex("├"), "E");
    return str;
}

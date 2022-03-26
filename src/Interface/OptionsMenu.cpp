// ****************************************************************************************************
// ****************************************** OPTIONS_MENU_CPP__ *****************************************
// ****************************************************************************************************

#include "OptionsMenu.h"
#include "Menu.h"

OptionsMenu::OptionsMenu(Controller& controller) : Menu(controller) {
    mainOptions = {
            "Set walking factor",
            "Set Max walking distance",
            "Set Username",
            "Go Back"
    };
}

void OptionsMenu::setWalkingFactor() {
    string input = anyInputMenu("From 1 to 10, how much do you like to walk?", "(Type 'B' to go back:)");
    while (!checkIntInput(input,1,10) && input!="B")
        input = anyInputMenu("From 1 to 10, how much do you like to walk?", "Invalid Input! (Type 'B' to go back:)");
    if(input == "B")
        return;
    controller->setWalkingFac(stoi(input));
    singleInputScreen("Walking Factor changed!\nNote that these changes will take effect only after a system restart");
}

void OptionsMenu::setMaxWalkingDistance() {
    string input = anyInputMenu("What is the maximum walking distance, in meters? (max: 250)", "(Type 'B' to go back:)");
    while (!checkIntInput(input, 1, 250) && input!="B")
        input = anyInputMenu("What is the maximum walking distance, in meters? (max: 250)", "Invalid Input! (Type 'B' to go back:)");
    if(input == "B")
        return;
    controller->setMaxWalkDist(stoi(input));
    singleInputScreen("Maximum distance changed!\nNote that these changes will take effect only after a system restart");
}

void OptionsMenu::setUsername() {
    string input = anyInputMenu("Please insert the new username", "(Or type 'B' to go back:)");
    if(input == "B")
        return;
    controller->setUsername(input);
}

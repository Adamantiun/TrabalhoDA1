//
// Created by Acer on 22/01/2022.
//

#ifndef UNTITLED_DIRECTIONSMENU_H
#define UNTITLED_DIRECTIONSMENU_H


#include "Menu.h"

class DirectionsMenu  : public Menu{
private:
    string origin;
    string destination;
    char currentInput;
public:
    DirectionsMenu(Controller& controller);
    bool insertId();
    bool searchByLine();
    bool searchByLoc();
    void nowGetting(char option);

    bool checkStopId(string basicString);

    void showDirections();

    bool insertCoordinates();

    bool checkLineId(string basicString);
};


#endif //UNTITLED_DIRECTIONSMENU_H

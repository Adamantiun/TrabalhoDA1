// ****************************************************************************************************
// ****************************************** OPTIONS_MENU_H__ *******************************************
// ****************************************************************************************************


#ifndef PROJ1_STARTMENU_H
#define PROJ1_STARTMENU_H

#include "Menu.h"

class OptionsMenu : public Menu{
public:
    OptionsMenu(Controller& controller);

    void setWalkingFactor();

    void setMaxWalkingDistance();

    void setUsername();
};

#endif //PROJ1_STARTMENU_H

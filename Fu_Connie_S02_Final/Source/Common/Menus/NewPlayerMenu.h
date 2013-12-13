#ifndef NEWPLAYERMENU_H
#define NEWPLAYERMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class NewPlayerMenu : public Menu
{
public:
    NewPlayerMenu();
    ~NewPlayerMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};

#endif
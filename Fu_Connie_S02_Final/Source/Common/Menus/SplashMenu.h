#ifndef SPLASHMENU_H
#define SPLASHMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class SplashMenu : public Menu
{
public:
    SplashMenu();
    ~SplashMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};

#endif
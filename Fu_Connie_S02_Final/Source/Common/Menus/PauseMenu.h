#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class PauseMenu : public Menu
{
public:
    PauseMenu();
    ~PauseMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};

#endif
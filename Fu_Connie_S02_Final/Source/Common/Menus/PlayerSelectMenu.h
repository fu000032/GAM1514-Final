#ifndef PLAYERSELECTMENU_H
#define PLAYERSELECTMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class PlayerSelectMenu : public Menu
{
public:
    PlayerSelectMenu();
    ~PlayerSelectMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);

	Level* m_Level;
};

#endif
#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class LevelSelectMenu : public Menu
{
public:
    LevelSelectMenu();
    ~LevelSelectMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
	Level* m_Level;
};

#endif
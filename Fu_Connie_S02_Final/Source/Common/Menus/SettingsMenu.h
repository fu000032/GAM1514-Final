#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class SettingsMenu : public Menu
{
public:
    SettingsMenu();
    ~SettingsMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);

	const char* m_PreviousMenuName;
};

#endif
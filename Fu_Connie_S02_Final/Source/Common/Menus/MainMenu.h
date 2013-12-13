#ifndef __GAM_1514_OSX_Game__MainMenu__
#define __GAM_1514_OSX_Game__MainMenu__

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIFont.h"


class MainMenu : public Menu
{
public:
    MainMenu();
    ~MainMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};

#endif

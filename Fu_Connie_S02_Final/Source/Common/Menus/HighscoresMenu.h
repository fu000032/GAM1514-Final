#ifndef HIGHSCORESMENU_H
#define HIGHSCORESMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


class HighscoresMenu : public Menu
{
public:
    HighscoresMenu();
    ~HighscoresMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);

	const char* m_PreviousMenuName;
};

#endif
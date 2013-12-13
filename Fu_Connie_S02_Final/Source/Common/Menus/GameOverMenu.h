#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIFont.h"

class GameOverMenu : public Menu
{
public:
	GameOverMenu();
	~GameOverMenu();

	const char* getName();

private:
	void buttonAction(UIButton* button);

	UIFont* m_GameOverFont;
};

#endif
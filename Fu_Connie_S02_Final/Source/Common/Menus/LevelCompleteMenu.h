#ifndef LEVELCOMPLETEMENU_H
#define LEVELCOMPLETEMENU_H

#include "Menu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIFont.h"

class LevelCompleteMenu : public Menu
{
public:
	LevelCompleteMenu();
	~LevelCompleteMenu();

	const char* getName();

private:
	void buttonAction(UIButton* button);

	UIFont* m_GameOverFont;
};

#endif
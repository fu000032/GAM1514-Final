#include "PauseMenu.h"

PauseMenu::PauseMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonResume"));
	addButton(new UIButton("ButtonRestart"));
	addButton(new UIButton("ButtonSettings"));
	addButton(new UIButton("ButtonHighscores"));
	addButton(new UIButton("ButtonLevelSelect"));
	addButton(new UIButton("ButtonMainMenu"));
}

PauseMenu::~PauseMenu()
{

}

const char* PauseMenu::getName()
{
    return PAUSE_MENU_SCREEN_NAME;
}

void PauseMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(index == 0)
	{
		//resume game
	}
	else if(index == 1)
	{
		// reload the level
	}
	else if(index == 2)
	{
		g_PreviousMenu = 1;
		ScreenManager::getInstance()->switchScreen(SETTINGS_MENU_SCREEN_NAME);
	}
	else if(index == 3)
	{
		g_PreviousMenu = 1;
		ScreenManager::getInstance()->switchScreen(HIGHSCORES_MENU_SCREEN_NAME);
	}
	else if(index == 4)
	{
		ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
	}
	else if(index == 5)
	{
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
 
}

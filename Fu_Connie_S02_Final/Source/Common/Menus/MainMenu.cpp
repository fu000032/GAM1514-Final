#include "MainMenu.h"

MainMenu::MainMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonStart"));
	addButton(new UIButton("ButtonSettings"));
	addButton(new UIButton("ButtonHighscores"));
	addButton(new UIButton("ButtonExit"));
}

MainMenu::~MainMenu()
{

}

const char* MainMenu::getName()
{
    return MAIN_MENU_SCREEN_NAME;
}

void MainMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(index == 0)
	{
		//ScreenManager::getInstance()->switchScreen(PLAYER_SELECT_MENU_SCREEN_NAME);
		ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
	}
	else if(index == 1)
	{
		g_PreviousMenu = 0;
		ScreenManager::getInstance()->switchScreen(SETTINGS_MENU_SCREEN_NAME);
	}
	else if(index == 2)
	{
		g_PreviousMenu = 0;
		ScreenManager::getInstance()->switchScreen(HIGHSCORES_MENU_SCREEN_NAME);
	}
	else if(index == 3)
	{
		exit(1);
	}
 
}

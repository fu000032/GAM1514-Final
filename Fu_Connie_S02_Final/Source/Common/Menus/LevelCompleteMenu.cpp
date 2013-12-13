#include "LevelCompleteMenu.h"

LevelCompleteMenu::LevelCompleteMenu() : Menu(NULL, NULL)
{
	m_GameOverFont = new UIFont("BitmapFont");
	m_GameOverFont->setText("game over");
	m_GameOverFont->draw(200.0f, 50.0f);

	// restart, main menu, level select
	addButton(new UIButton("ButtonRestart"));
	addButton(new UIButton("ButtonMainMenu"));
	addButton(new UIButton("ButtonLevelSelect"));
}

LevelCompleteMenu::~LevelCompleteMenu()
{
	if(m_GameOverFont != NULL)
	{
		delete m_GameOverFont;
		m_GameOverFont = NULL;
	}
}

const char* LevelCompleteMenu::getName()
{
	return LEVEL_COMPLETE_MENU_SCREEN_NAME;
}

void LevelCompleteMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(index == 0)
	{
		//restart
	}
	else if(index == 1)
	{
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
	else if(index == 2)
	{
		ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
	}
}
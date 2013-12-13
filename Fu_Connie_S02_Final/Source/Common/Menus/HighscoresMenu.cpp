#include "HighscoresMenu.h"

HighscoresMenu::HighscoresMenu() : Menu(NULL, NULL)
{
    // buttons along left side with levels
	// main area with highscores (player name and score)
	addButton(new UIButton("ButtonBack"));
}

HighscoresMenu::~HighscoresMenu()
{

}

const char* HighscoresMenu::getName()
{
	return HIGHSCORES_MENU_SCREEN_NAME;
}

void HighscoresMenu::buttonAction(UIButton* button)
{
	if(g_PreviousMenu == 0)
	{
		m_PreviousMenuName = MAIN_MENU_SCREEN_NAME;
	}
	else
	{
		m_PreviousMenuName = PAUSE_MENU_SCREEN_NAME;
	}

	int index = getIndexForButton(button);

	// when level buttons clicked, load that level's highscores

	if(index == 0)
	{
		ScreenManager::getInstance()->switchScreen(m_PreviousMenuName);
	}
}

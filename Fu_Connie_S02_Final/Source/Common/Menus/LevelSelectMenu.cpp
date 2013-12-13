#include "LevelSelectMenu.h"

LevelSelectMenu::LevelSelectMenu() : Menu(NULL, NULL),
	m_Level(NULL)
{
    // Levels
	addButton(new UIButton("Level1"));
	addButton(new UIButton("Level2"));
	addButton(new UIButton("Level3"));

	addButton(new UIButton("ButtonBack"));

	Game* game = (Game*)ScreenManager::getInstance() -> getScreenForName(GAME_SCREEN_NAME);
	m_Level = game -> getLevel();
}

LevelSelectMenu::~LevelSelectMenu()
{

}

const char* LevelSelectMenu::getName()
{
    return LEVEL_SELECT_MENU_SCREEN_NAME;
}

void LevelSelectMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	// when level is clicked, load level

	if(index == 0)
	{
		g_PlayerSpawn = 16;
		g_EnemySpawn = 44;
		m_Level->loadLevel("Level1.json");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
	else if(index == 1)
	{
		g_PlayerSpawn = 28;
		g_EnemySpawn = 105;
		m_Level->loadLevel("Level2.json");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
	else if(index == 2)
	{
		g_PlayerSpawn = 118;
		g_EnemySpawn = 7;
		m_Level->loadLevel("Level3.json");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
	else if(index == 3)
	{
		//ScreenManager::getInstance()->switchScreen(PLAYER_SELECT_MENU_SCREEN_NAME);
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
}

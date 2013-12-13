#include "SaveMenu.h"

SaveMenu::SaveMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("Slot1"));
	addButton(new UIButton("Slot2"));
	addButton(new UIButton("Slot3"));
	addButton(new UIButton("Slot4"));
	addButton(new UIButton("Slot5"));
	addButton(new UIButton("Slot6"));
	addButton(new UIButton("ButtonExit"));
}

SaveMenu::~SaveMenu()
{

}

const char* SaveMenu::getName()
{
	return SAVE_MENU_SCREEN_NAME;
}

void SaveMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(m_Save == 0 || m_Save == 1)
	{
		if(m_Save == 0) // save
		{
			if(index == 0)
			{
				m_Level->save("Level1.json");
			}
			else if(index == 1)
			{
				m_Level->save("Level2.json");
			}
			else if (index == 2)
			{
				m_Level->save("Level3.json");
			}
			else if (index == 3)
			{
				m_Level->save("Level4.json");
			}
			else if (index == 4)
			{
				m_Level->save("Level5.json");
			}
			else if (index == 5)
			{
				m_Level->save("Level6.json");
			}
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (m_Save == 1) // load
		{
			if(index == 0)
			{
				m_Level->load("Level1.json");
			}
			else if(index == 1)
			{
				m_Level->load("Level2.json");
			}
			else if (index == 2)
			{
				m_Level->load("Level3.json");
			}
			else if (index == 3)
			{
				m_Level->load("Level4.json");
			}
			else if (index == 4)
			{
				m_Level->load("Level5.json");
			}
			else if (index == 5)
			{
				m_Level->load("Level6.json");
			}
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}

		if (index == 6)
		{
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
	}
	else // load and go to game
	{
		if(index != 6)
		{
			if(index == 0)
			{
				m_Level->load("Level1.json");
			}
			else if(index == 1)
			{
				m_Level->load("Level2.json");
			}
			else if (index == 2)
			{
				m_Level->load("Level3.json");
			}
			else if (index == 3)
			{
				m_Level->load("Level4.json");
			}
			else if (index == 4)
			{
				m_Level->load("Level5.json");
			}
			else if (index == 5)
			{
				m_Level->load("Level6.json");
			}
			ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
		}
		else if (index == 6)
		{
			ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
		}
	}
}

void SaveMenu::setSave(int save)
{
	m_Save = save;
}

int SaveMenu::getSave()
{
	return m_Save;
}

void SaveMenu::setLevel(Level* level)
{
	m_Level = level;
}
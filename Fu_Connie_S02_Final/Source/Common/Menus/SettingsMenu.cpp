#include "SettingsMenu.h"

SettingsMenu::SettingsMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonBack"));
}

SettingsMenu::~SettingsMenu()
{

}

const char* SettingsMenu::getName()
{
    return SETTINGS_MENU_SCREEN_NAME;
}

void SettingsMenu::buttonAction(UIButton* button)
{
	if(g_PreviousMenu == 0)
	{
		m_PreviousMenuName = MAIN_MENU_SCREEN_NAME;
	}
	else if(g_PreviousMenu == 1)
	{
		m_PreviousMenuName = PAUSE_MENU_SCREEN_NAME;
	}

	int index = getIndexForButton(button);

	if(index == 0)
	{
		ScreenManager::getInstance()->switchScreen(m_PreviousMenuName);
	}

}

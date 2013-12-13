#include "NewPlayerMenu.h"

NewPlayerMenu::NewPlayerMenu() : Menu(NULL, NULL)
{
	// typing spot for a new player name

    // Create and Start
	// Cancel/back
	addButton(new UIButton("ButtonCreate"));
	addButton(new UIButton("ButtonBack"));
}

NewPlayerMenu::~NewPlayerMenu()
{

}

const char* NewPlayerMenu::getName()
{
    return NEW_PLAYER_MENU_SCREEN_NAME;
}

void NewPlayerMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(index == 0)
	{
		// check if text box is empty
		// save new player to slot that was clicked
		ScreenManager::getInstance()->switchScreen(PLAYER_SELECT_MENU_SCREEN_NAME);
	}
	else if(index == 1)
	{
		ScreenManager::getInstance()->switchScreen(PLAYER_SELECT_MENU_SCREEN_NAME);
	}
}

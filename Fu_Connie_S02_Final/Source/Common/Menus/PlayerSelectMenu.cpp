#include "PlayerSelectMenu.h"


PlayerSelectMenu::PlayerSelectMenu() : Menu(NULL, NULL)
{
	// slot 1-3
	
	// load players... if there is a player in a slot,
	// it will load a name else it will load empty slot
	// These buttons lined up vertically in middle of screen

	/*addButton(new UIButton(SLOT1_NAME));
	addButton(new UIButton(SLOT2_NAME));
	addButton(new UIButton(SLOT3_NAME));*/

    // These buttons need to be lined up horizontally at bottom of screen ... 
	addButton(new UIButton("ButtonNewGame"));
	addButton(new UIButton("ButtonLoadGame"));
	addButton(new UIButton("ButtonBack"));
}

PlayerSelectMenu::~PlayerSelectMenu()
{

}

const char* PlayerSelectMenu::getName()
{
    return PLAYER_SELECT_MENU_SCREEN_NAME;
}

void PlayerSelectMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(index == 3) //new player
	{
		// check if player selected
		// check if there is already a player in slot
			// if so -> would you like to delete this player? yes/no
				// yes: new player screen
				// no: back to player select
			// if not-> new player screen
		
		ScreenManager::getInstance()->switchScreen(NEW_PLAYER_MENU_SCREEN_NAME);
	}
	else if(index == 4) //load player
	{
		// check if player selected
		// if there is a player, load player
		// if not, new player screen 

		ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
	}
	else if(index == 5)
	{
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
 
}

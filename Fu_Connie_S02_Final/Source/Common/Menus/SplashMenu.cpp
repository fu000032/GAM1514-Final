#include "SplashMenu.h"

SplashMenu::SplashMenu() : Menu(NULL, NULL)
{
    // HAHAHHAHHAHAHAHHHAHHAHAHA ... lazy as fuck FOR NOW
	addButton(new UIButton("ButtonBlank"));
	addButton(new UIButton("ButtonBlank"));
	addButton(new UIButton("ButtonBlank"));
	addButton(new UIButton("ButtonBlank"));
	addButton(new UIButton("ButtonBlank"));

	// Click to Begin
	addButton(new UIButton("ButtonClickToBegin"));
}

SplashMenu::~SplashMenu()
{

}

const char* SplashMenu::getName()
{
    return SPLASH_MENU_SCREEN_NAME;
}

void SplashMenu::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);

	if(index == 5)
	{
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
 
}

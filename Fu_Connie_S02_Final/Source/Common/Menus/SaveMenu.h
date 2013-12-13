//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Save Menu class
// Modified:		Connie Fu 
//

#ifndef SAVEMENU_H
#define SAVEMENU_H

#include "Menu.h"

#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"

// This is the SaveMenu class
// it inherits from Menu
// it sets up the Save Menu
class SaveMenu : public Menu
{
public:
	SaveMenu();
	~SaveMenu();

	const char* getName();

	void setSave(int save);
	int getSave();

	void setLevel(Level* level);


private:
	void buttonAction(UIButton* button);
	Level* m_Level;

	int m_Save;
};

#endif
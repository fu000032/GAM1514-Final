//
//  LevelEditor.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Level Editor class
// Modified:		Connie Fu 
//


#ifndef __GAM_1514_OSX_Game__LevelEditor__
#define __GAM_1514_OSX_Game__LevelEditor__

#include "../Screen Manager/Screen.h"
#include "../UI/UISideMenu.h"
#include "../Menus/SaveMenu.h"

class UISideMenu;
class Level;

// This is the Level class
// it inherits from Screen and UISideMenuListener
// it sets up the level editor 
class LevelEditor : public Screen, public UISideMenuListener
{
public:
	LevelEditor();
	~LevelEditor();

	const char* getName();

	void update(double delta);
	void paint();
	void reset();

	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickDownEvent(float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void keyUpEvent(int keyCode);

private:
	void sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex);
	void sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex);

	UISideMenu* m_OptionsMenu;
	UISideMenu* m_TilesMenu;
	Level* m_Level;

	bool m_IsMouseDown;
	int m_SelectedTileIndex;
	int m_SelectedOptionIndex;

	SaveMenu* m_SaveMenu;
};

#endif /* defined(__GAM_1514_OSX_Game__LevelEditor__) */

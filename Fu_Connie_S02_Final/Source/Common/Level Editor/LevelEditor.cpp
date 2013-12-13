//
//  LevelEditor.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "LevelEditor.h"
#include "../Constants/Constants.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"


LevelEditor::LevelEditor() :
m_TilesMenu(NULL),
	m_Level(NULL),
	m_IsMouseDown(false),
	m_SelectedTileIndex(-1),
	m_SelectedOptionIndex(-1)
{
	//Create the Tiles menu items
	m_TilesMenu = new UISideMenu(this, SideMenuRight);
	m_TilesMenu->addButton(new UIToggle("MenuTileGround"));
	m_TilesMenu->addButton(new UIToggle("MenuTileGrass"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
	m_TilesMenu->addButton(new UIToggle("MenuTilePath"));
	m_TilesMenu->addButton(new UIToggle("MenuTileCat"));
	m_TilesMenu->addButton(new UIToggle("MenuTileBush"));

	//Create Options Side Menu items
	m_OptionsMenu = new UISideMenu(this, SideMenuLeft);
	m_OptionsMenu->addButton(new UIButton("SaveOption"));
	m_OptionsMenu->addButton(new UIButton("LoadOption"));
	m_OptionsMenu->addButton(new UIButton("ClearOption"));
	m_OptionsMenu->addButton(new UIButton("ExitOption"));

	//Create the level object
	m_Level = new Level(true);


	m_SaveMenu = (SaveMenu*)ScreenManager::getInstance()->getScreenForName(SAVE_MENU_SCREEN_NAME);

	//Reset everything
	reset();
}

LevelEditor::~LevelEditor()
{
	if(m_Level != NULL)
	{
		delete m_Level;
		m_Level = NULL;
	}

	if(m_TilesMenu != NULL)
	{
		delete m_TilesMenu;
		m_TilesMenu = NULL;
	}

	if(m_OptionsMenu != NULL)
	{
		delete m_OptionsMenu;
		m_OptionsMenu = NULL;
	}

	if(m_SaveMenu != NULL)
	{
		m_SaveMenu = NULL;
	}
}

const char* LevelEditor::getName()
{
	return LEVEL_EDITOR_SCREEN_NAME;
}

void LevelEditor::update(double delta)
{
	if(m_Level != NULL)
	{
		m_Level->update(delta);
	}

	if(m_TilesMenu != NULL)
	{
		m_TilesMenu->update(delta);
	}

	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->update(delta);
	}
}

void LevelEditor::paint()
{
	if(m_Level != NULL)
	{
		m_Level->paint();
	}

	if(m_TilesMenu != NULL)
	{
		m_TilesMenu->paint();
	}

	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->paint();
	}
}

void LevelEditor::reset()
{
	if(m_Level != NULL)
	{
		m_Level->reset();
	}
}

void LevelEditor::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{    
	if(m_TilesMenu != NULL)
	{
		m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}

	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}

	if(m_Level != NULL)
	{        
		if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
		{
			m_Level->setTileTypeAtPosition((TileType)m_SelectedTileIndex, positionX, positionY);
		}
	}
}

void LevelEditor::mouseLeftClickDownEvent(float positionX, float positionY)
{
	//Set the mouse down flag
	m_IsMouseDown = true;
}

void LevelEditor::mouseLeftClickUpEvent(float positionX, float positionY)
{
	//Set the mouse up flag
	m_IsMouseDown = false;

	//Safety check the level pointer, then set the new tile type in the index
	if(m_Level != NULL)
	{
		if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
		{
			m_Level->setTileTypeAtPosition((TileType)m_SelectedTileIndex, positionX, positionY);
		}
	}

	//Notify the tiles menu of the mouse event
	if(m_TilesMenu != NULL)
	{
		m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
	}

	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->mouseLeftClickUpEvent(positionX, positionY);
	}
}

void LevelEditor::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_TAB)
	{
		if(m_TilesMenu != NULL)
		{
			m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
		}

		if(m_OptionsMenu != NULL)
		{
			m_OptionsMenu->isShowing() == true ? m_OptionsMenu->hide() : m_OptionsMenu->show();
		}
	}
	else
	{
		if(m_Level != NULL)
		{
			m_Level->keyUpEvent(keyCode);
		}
	}
}

void LevelEditor::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
	if(sideMenu == m_OptionsMenu)
	{
		if(buttonIndex == 0) // save
		{
			m_SaveMenu->setLevel(m_Level);
			m_SaveMenu->setSave(0);
			ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
		}
		if(buttonIndex == 1) // load
		{
			m_SaveMenu->setLevel(m_Level);
			m_SaveMenu->setSave(1);
			ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
		}
		if(buttonIndex == 2) // clear
		{
			for(int i = 0; i < m_Level->getNumberOfTiles() ; i++)
			{
				m_Level->setTileTypeAtIndex(TileTypeGround, i);
			}
		}
		if(buttonIndex == 3)// exit (goes back to main menu)
		{
			ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
		}
	}
}

void LevelEditor::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
	if(sideMenu == m_TilesMenu)
	{
		//Un-toggled the previously selected toggle
		UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
		if(previousToggle != NULL)
		{
			previousToggle->setIsToggled(false);
		}

		//Set the selected tile index
		m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;

		//Hide the options and tiles menus
		m_TilesMenu->hide();
		m_OptionsMenu->hide();
	}

	if(sideMenu == m_OptionsMenu)
	{
		//Hide the options and tiles menus
		m_TilesMenu->hide();
		m_OptionsMenu->hide();
	}
}

//
//  MenuConstants.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-08.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MenuConstants.h"


const float UI_SIDE_MENU_SPEED = 750.0f;

const float MENU_TITLE_Y_PERCENTAGE = 0.078125f;
const float MENU_ITEMS_STARTING_Y_PERCENTAGE = 0.3527f;
const float MENU_ITEMS_SPACER_PERCENTAGE = 0.1171875f;

const char* MAIN_MENU_SCREEN_NAME = "MainMenu";
const char* SAVE_MENU_SCREEN_NAME = "SaveMenu";
const char* HIGHSCORES_MENU_SCREEN_NAME = "HighscoresMenu";
const char* LEVEL_SELECT_MENU_SCREEN_NAME = "LevelSelectMenu";
const char* NEW_PLAYER_MENU_SCREEN_NAME = "NewPlayerMenu";
const char* PAUSE_MENU_SCREEN_NAME = "PauseMenu";
const char* PLAYER_SELECT_MENU_SCREEN_NAME = "PlayerSelectMenu";
const char* SETTINGS_MENU_SCREEN_NAME = "SettingsMenu";
const char* SPLASH_MENU_SCREEN_NAME = "SplashMenu";
const char* GAME_OVER_MENU_SCREEN_NAME = "GameOverMenu";
const char* LEVEL_COMPLETE_MENU_SCREEN_NAME = "LevelCompleteMenu";

int g_PreviousMenu = 0; // 0 = main menu, 1 = pause menu


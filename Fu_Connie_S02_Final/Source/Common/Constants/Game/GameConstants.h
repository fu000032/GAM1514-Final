#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../OpenGL/OpenGLColor.h"

//Game Constants
extern const char* GAME_SCREEN_NAME;

//Tile Constants
extern const char* TILE_GROUND_TYPE;
extern const char* TILE_GRASS_TYPE;
extern const char* TILE_WATER_TYPE;
extern const char* TILE_PATH_TYPE;
extern const char* TILE_BUSH_TYPE;
extern const char* TILE_CAT_TYPE;

extern const int TILE_PADDING;

//Player Constants
extern const int PLAYER_SIZE;
extern const float PLAYER_SPEED;
extern const OpenGLColor PLAYER_INSIDE_COLOR;
extern const OpenGLColor PLAYER_OUTLINE_COLOR;

//Hero Constants
extern const char* HERO_TYPE;

//Enemy Constants
extern const char* ENEMY_TYPE;
extern const int ENEMY_COUNT;

extern int g_EnemySpawn;
extern int g_PlayerSpawn;

#endif 
#include "GameConstants.h"


//Game Constants
const char* GAME_SCREEN_NAME = "Game";

//Tiles Constants
const char* TILE_GROUND_TYPE = "GroundTile";
const char* TILE_GRASS_TYPE = "GrassTile";
const char* TILE_WATER_TYPE = "WaterTile";
const char* TILE_PATH_TYPE = "PathTile";
const char* TILE_BUSH_TYPE = "BushTile";
const char* TILE_CAT_TYPE = "CatTile";

const int TILE_PADDING = 2;

//Player Constants
const int PLAYER_SIZE = 24;
const float PLAYER_SPEED = 150.0f;
const OpenGLColor PLAYER_INSIDE_COLOR = OpenGLColorBlack();
const OpenGLColor PLAYER_OUTLINE_COLOR = OpenGLColor(1.0f, 1.0f, 1.0f, 1.0f);

//Hero Constants
const char* HERO_TYPE = "Hero";

//Enemy Constants
const char* ENEMY_TYPE = "Enemy";
const int ENEMY_COUNT = 10;

int g_EnemySpawn  = 0;
int g_PlayerSpawn = 0;
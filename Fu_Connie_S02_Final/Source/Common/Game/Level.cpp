//
//  Level.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Level.h"
#include "Player.h"
#include "Tiles/Tile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/GrassTile.h"
#include "Tiles/WaterTile.h"
#include "Tiles/PathTile.h"
#include "Tiles/BushTile.h"
#include "Tiles/CatTile.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "PathFinder.h"
#include "PathNode.h"
#include <stdlib.h>
#include <fstream>
#include "Enemy.h"
#include "Hero.h"
#include "../Utils/Utils.h"

#include "../Libraries/jsoncpp/json.h"


Level::Level(bool isEditingLevel) :
m_HorizontalTiles(0),
	m_VerticalTiles(0),
	m_TileSize(EMPTY_LEVEL_TILE_SIZE),
	m_PlayerStartingTileIndex(EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX),
	m_Hero(NULL),
	m_Tiles(NULL),
	m_SelectedTileIndex(-1),
	m_PaintTileScoring(false),
	m_PaintTileIndexes(false),
	m_EnemySpawnTimer(2.0)
{
	//Create the player object
	if(isEditingLevel == false)
	{
		m_Hero = new Hero(this);

		//spawnEnemy();
	}

	//Calculate the number of horizontal and vertical tiles
	m_HorizontalTiles	= 15;
	m_VerticalTiles		= 10;

	//Allocate the tiles array, the inheriting class will populate this array with Tile objects
	m_Tiles = new Tile*[m_HorizontalTiles * m_VerticalTiles];

	//Initialize all the tiles to NULL
	for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
	{
		m_Tiles[i] = NULL;
	}

	m_UIBackground = new OpenGLTexture("GameUIBackground");

	m_OffsetX = TILE_STARTING_X;
	m_OffsetY = TILE_STARTING_Y;

	//Load an empty level
	loadLevel(NULL);
}

Level::~Level()
{
	//Delete the player object
	if(m_Hero != NULL)
	{
		delete m_Hero;
		m_Hero = NULL;
	}

	for(int i = 0; i < m_Enemies.size(); i++)
	{
		delete m_Enemies.at(i);
		m_Enemies.at(i) = NULL;
	}
	m_Enemies.clear();

	//Delete the tiles array, the inheriting class
	//must delete the object in this array itself
	if(m_Tiles != NULL)
	{
		//Cycle through and delete all the tile objects in the array
		for(int i = 0; i < getNumberOfTiles(); i++)
		{
			if(m_Tiles[i] != NULL)
			{
				delete m_Tiles[i];
				m_Tiles[i] = NULL;
			}
		}

		delete[] m_Tiles;
		m_Tiles = NULL;
	}

	if(m_UIBackground != NULL)
	{
		delete m_UIBackground;
		m_UIBackground = NULL;
	}
}

void Level::update(double aDelta)
{
	//Update all the game tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->update(aDelta);
		}
	}

	//Update the Hero
	if(m_Hero != NULL)
	{
		m_Hero->update(aDelta);
	}

	m_EnemySpawnTimer -= aDelta;
	if(m_EnemySpawnTimer < 0.0)
	{
		spawnEnemy();
		m_EnemySpawnTimer = 2.0f;
	}
	for(int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->update(aDelta);
	}
}

void Level::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_UIBackground, 0.0f, 0.0f);

	//Cycle through and paint all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		//Safety check the tile
		if(m_Tiles[i] != NULL)
		{
			//Paint the tile
			m_Tiles[i]->paint();

			//If the paint tile indexes flag is set to true,
			//draw the index number on the tiles
			if(m_PaintTileIndexes == true)
			{
				m_Tiles[i]->paintIndex(i);
			}
		}
	}

	//Paint the Hero
	if(m_Hero != NULL)
	{
		//If paint tile scoring flag is set to true,
		//draw the path scoring
		if(m_PaintTileScoring == true)
		{
			m_Hero->getPathFinder()->paint();
		}

		//Paint the player
		m_Hero->paint();
	}

	for(int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->paint();
	}


}

void Level::reset()
{
	//Cycle through and reset all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->reset();
		}
	}

	//Reset the Player
	if(m_Hero != NULL)
	{
		m_Hero->reset();
		m_Hero->setCurrentTile(m_Tiles[m_PlayerStartingTileIndex]);
	}

	//Player* vector
	std::vector<Player*> players;

	if(m_Hero != NULL)
	{
		players.push_back(m_Hero);
	}

	for(int i = 0; i < m_Enemies.size(); i++)
	{
		players.push_back(m_Enemies.at(i));
	}

	//spawn enemies
	for(int i = 0; i < players.size(); i++)
	{
		if(players.at(i) == m_Hero)
		{
			players.at(i)->setCurrentTile(getTileForIndex(g_PlayerSpawn));
		}
		else
		{
			players.at(i)->setCurrentTile(getTileForIndex(g_EnemySpawn)); // change later
		}
		players.at(i)->reset();
	}
}

void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
	if(m_Hero != NULL)
	{
		m_Hero->mouseLeftClickUpEvent(aPositionX, aPositionY);
	}
}

void Level::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_R)
	{
		reset();
	}
	else if(keyCode == KEYCODE_S)
	{
		togglePaintTileScoring();
	}
	else if(keyCode == KEYCODE_I)
	{
		togglePaintTileIndexes();
	}
	else if(keyCode == KEYCODE_D)
	{
		/*if(m_Player != NULL)
		{
		m_Player->getPathFinder()->togglePathFindingDelay();
		}*/
	}
}

void Level::loadLevel(const char* levelName)
{
	//If the level name isn't NULL load the level from the filesystem,
	//if it is NULL load an empty level with just ground tiles
	if(levelName != NULL)
	{
		Json::Value root;
		Json::Reader reader;

		std::ifstream in(levelName);

		bool success = reader.parse(in, root);

		const Json::Value tileTypeArray = root["tileTypeArray"];


		for(int i = 0; i < tileTypeArray.size(); i++)
		{
			int tileType = tileTypeArray[i].asInt();
			setTileTypeAtIndex((TileType)tileType, i);
		}

		in.close();
	}
	else
	{
		//Tile variables
		int tileIndex = 0;
		float tileX = m_OffsetX;
		float tileY = m_OffsetY;

		//Cycle through all the tiles and create them
		for(int v = 0; v < getNumberOfVerticalTiles(); v++)
		{
			for(int h = 0; h < getNumberOfHorizontalTiles(); h++)
			{
				//The empty level will contain only ground tiles
				m_Tiles[tileIndex] = new GroundTile();
				m_Tiles[tileIndex]->setPosition(tileX, tileY);
				m_Tiles[tileIndex]->setSize(m_TileSize, m_TileSize);

				//Increment the tile index
				tileIndex++;

				//And increment the tile x position
				tileX += m_TileSize;
			}

			//Increment the tile y position and reset the tile x position, since we started a new row
			tileY += m_TileSize;
			tileX = m_OffsetX;
		}
	}

	//The level is loaded, reset everything
	reset();
}

void Level::savePlayer(const char* playerName, int currentLevel, int slotNumber)
{
	Json::Value root;

	root["slotNumber"] = slotNumber;
	root["playerName"] = playerName;
	root["currentLevel"] = currentLevel;

	//array of scores
	Json::Value scores;

	for(int i = 0; i < 5;i++)
	{
		//save scores to level (5 levels)
	}

	std::ofstream out;
	out.open((const char*)slotNumber);
	out << root;
	out.close();
}

void Level::loadPlayer(int slotNumber)
{
	//if player isnt NULL, load from file
	//if it is NULL go to new player screen
	if(slotNumber != NULL)
	{
		//TODO: save the level
		Json::Value root;
		Json::Reader reader;

		std::ifstream in((const char*)slotNumber);

		bool success = reader.parse(in, root);

		const char* player = root.get("playerName", 0).asCString();
		int level = root.get("currentLevel", 0).asInt();

		//set levels that are unlocked based on current level

		in.close();
	}
	else
	{
		ScreenManager::getInstance()->switchScreen(NEW_PLAYER_MENU_SCREEN_NAME);
	}
}

TileType Level::getTileTypeForIndex(int index)
{
	if(index >= 0 && index < getNumberOfTiles())
	{
		return m_Tiles[index]->getTileType();
	}
	return TileTypeUnknown;
}

unsigned int Level::getNumberOfTiles()
{
	return getNumberOfHorizontalTiles() * getNumberOfVerticalTiles();
}

unsigned int Level::getNumberOfHorizontalTiles()
{
	return m_HorizontalTiles;
}

unsigned int Level::getNumberOfVerticalTiles()
{
	return m_VerticalTiles;
}

bool Level::validateTileCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	if(aCoordinatesX < 0 || aCoordinatesY < 0 || aCoordinatesX >= getNumberOfHorizontalTiles() || aCoordinatesY >= getNumberOfVerticalTiles())
	{
		return false;
	}
	return true;
}

int Level::getTileCoordinateForPositionX(int aPositionX)
{
	return ((aPositionX - m_OffsetX) / m_TileSize);
}

int Level::getTileCoordinateForPositionY(int aPositionY)
{
	return ((aPositionY - m_OffsetY) / m_TileSize);
}

int Level::getTileIndexForPosition(int aPositionX, int aPositionY)
{
	int coordinatesX = getTileCoordinateForPositionX(aPositionX);
	int coordinatesY = getTileCoordinateForPositionY(aPositionY);
	return getTileIndexForCoordinates(coordinatesX, coordinatesY);
}

int Level::getTileIndexForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	//Validate the coordinates, then calculate the array index
	if(validateTileCoordinates(aCoordinatesX, aCoordinatesY) == true)
	{
		return aCoordinatesX + (aCoordinatesY * getNumberOfHorizontalTiles());
	}

	return -1;
}

int Level::getTileIndexForTile(Tile* aTile)
{
	return getTileIndexForPosition(aTile->getX(), aTile->getY());
}

int Level::getTileIndexForPlayer(Player* player)
{
	return getTileIndexForPosition(player->getX(), player->getY());
}

Tile* Level::getTileForPosition(int aPositionX, int aPositionY)
{
	return getTileForIndex(getTileIndexForPosition(aPositionX, aPositionY));
}

Tile* Level::getTileForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	return getTileForIndex(getTileIndexForCoordinates(aCoordinatesX, aCoordinatesY));
}

Tile* Level::getTileForIndex(int aIndex)
{
	//Safety check the index bounds
	if(aIndex >= 0 && aIndex < getNumberOfTiles())
	{
		return m_Tiles[aIndex];
	}

	//If we got here, it means the index passed in was out of bounds
	return NULL;
}

Tile* Level::getTileForPlayer(Player* player)
{
	return getTileForPosition(player->getX(), player->getY());
}

void Level::setTileTypeAtPosition(TileType tileType, int positionX, int positionY)
{
	setTileTypeAtIndex(tileType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY)
{
	setTileTypeAtIndex(tileType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTileTypeAtIndex(TileType tileType, int index)
{
	//Safety check the index
	if(index >= 0 && index < getNumberOfTiles())
	{
		//Don't replace the tile if its the same type of tile that already exists
		if(m_Tiles[index]->getTileType() == tileType)
		{
			return;
		}

		int previousX = 0;
		int previousY = 0;

		//Delete the tile at the index, if one exists
		if(m_Tiles[index] != NULL)
		{
			previousX = m_Tiles[index] -> getX();
			previousY = m_Tiles[index] -> getY();

			delete m_Tiles[index];
			m_Tiles[index] = NULL;
		}

		//Create the new tile based on the TileType
		switch (tileType)
		{
		case TileTypeGround:
			m_Tiles[index] = new GroundTile();
			break;
		case TileTypeGrass:
			m_Tiles[index] = new GrassTile();
			break;
		case TileTypeWater:
			m_Tiles[index] = new WaterTile();
			break;
		case TileTypePath:
			m_Tiles[index] = new PathTile();
			break;
		case TileTypeBush:
			m_Tiles[index] = new BushTile();
			break;
		case TileTypeCat:
			m_Tiles[index] = new CatTile();
			break;

		case TileTypeUnknown:
		default:
			m_Tiles[index] = NULL;
			break;
		}

		//Calculate the coordinates and set the tile position and size
		m_Tiles[index]->setPosition(previousX, previousY);
		m_Tiles[index]->setSize(m_TileSize, m_TileSize);
	}
}

void Level::togglePaintTileScoring()
{
	m_PaintTileScoring = !m_PaintTileScoring;
}

void Level::togglePaintTileIndexes()
{
	m_PaintTileIndexes = !m_PaintTileIndexes;
}

void Level::setSelectedTileIndex(int aSelectedIndex)
{
	//Deselect the previously selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(false);
	}

	//Set the new tile index
	m_SelectedTileIndex = aSelectedIndex;

	//Selected the newly selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(true);
	}
}


Hero* Level::getHero()
{
	return m_Hero;
}

void Level::spawnEnemy()
{
	float min = 50.0f;
	float max = 400.0f;
	// random enemy speeds
	GDRandom random;
	random.randomizeSeed();

	//Create enemy objects
	float speed = min + random.random(max-min);

	Enemy* enemy = new Enemy(this, speed);
	enemy->setCurrentTile(getTileForIndex(g_EnemySpawn));
	enemy->setDestinationTile(getTileForIndex(g_PlayerSpawn));
	m_Enemies.push_back(enemy);
}


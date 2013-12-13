//
//  Level.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Level class
// Modified:		Connie Fu 
//


#ifndef LEVEL_H
#define LEVEL_H

#include "../Constants/Constants.h"
#include <vector>

class OpenGLTexture;

class Tile;
class Player;
class Enemy;
class Hero;

// This is the Level class
// it creates, loads, and saves the level
class Level
{
public:
	Level(bool isEditingLevel = false);
	~Level();

	//Update, paint and reset methods
	void update(double delta);
	void paint();
	void reset();

	//
	void loadLevel(const char* levelName);

	void savePlayer(const char* playerName, int currentLevel, int slotNumber);
	void loadPlayer(int slotNumber);

	//void saveHighscores();
	//void loadHighscores();

	//Input methods
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void keyUpEvent(int keyCode);

	//
	TileType getTileTypeForIndex(int index);

	//Tile count methods
	unsigned int getNumberOfTiles();
	unsigned int getNumberOfHorizontalTiles();
	unsigned int getNumberOfVerticalTiles();

	//Validate that the tile coordinates passed in are valid
	bool validateTileCoordinates(int coordinatesX, int coordinatesY);

	//Converts a position in screen space into a position in coordinate space
	int getTileCoordinateForPositionX(int positionX);
	int getTileCoordinateForPositionY(int positionY);

	//Index methods
	int getTileIndexForPosition(int positionX, int positionY);
	int getTileIndexForCoordinates(int coordinatesX, int coordinatesY);
	int getTileIndexForTile(Tile* tile);
	int getTileIndexForPlayer(Player* player);

	//Tile methods
	Tile* getTileForPosition(int positionX, int positionY);
	Tile* getTileForCoordinates(int coordinatesX, int coordinatesY);
	Tile* getTileForIndex(int index);
	Tile* getTileForPlayer(Player* player);

	//
	void setTileTypeAtPosition(TileType tileType, int positionX, int positionY);
	void setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY);
	void setTileTypeAtIndex(TileType tileType, int index);

	//Coveniance methods to toggle debug paint methods
	void togglePaintTileScoring();
	void togglePaintTileIndexes();

	//Disables the old tiles selection (if ground tile) and
	//enables the newly selected tiles selection (if ground tile)
	void setSelectedTileIndex(int selectedIndex);

	//getter for hero
	Hero* getHero();

	void spawnEnemy();

protected:
	//Protected Member variables
	Hero* m_Hero;
	std::vector<Enemy*> m_Enemies;
	Tile** m_Tiles;
	unsigned int m_HorizontalTiles;
	unsigned int m_VerticalTiles;
	unsigned int m_TileSize;
	unsigned int m_OffsetX;
	unsigned int m_OffsetY;
	unsigned int m_PlayerStartingTileIndex;
	int m_SelectedTileIndex;
	bool m_PaintTileScoring;
	bool m_PaintTileIndexes;

	double m_EnemySpawnTimer;

	//UI variables
	OpenGLTexture* m_UIBackground;
};

#endif

//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Water Tile class
// Modified:		... 
//

#ifndef WATER_TILE_H
#define WATER_TILE_H

#include "Tile.h"

// This is the WaterTile class that inherits from Tile 
// and creates this tile for the game
class WaterTile : public Tile
{
public:
	WaterTile(const char* textureName = RES_TILE_WATER);
	virtual ~WaterTile();

	//Return the type of the tile
	const char* getType();

	bool isWalkableTile();
};

#endif
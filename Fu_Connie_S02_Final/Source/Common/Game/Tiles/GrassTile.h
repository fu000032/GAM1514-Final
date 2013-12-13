//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Grass Tile class
// Modified:		... 
//

#ifndef GRASS_TILE_H
#define GRASS_TILE_H

#include "Tile.h"

// This is the GrassTile class that inherits from Tile 
// and creates this tile for the game
class GrassTile : public Tile
{
public:
	GrassTile(const char* textureName = RES_TILE_GRASS);
	virtual ~GrassTile();

	//Return the type of the tile
	const char* getType();

	bool isWalkableTile();
};

#endif
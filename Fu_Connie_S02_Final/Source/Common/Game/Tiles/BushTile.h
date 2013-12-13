//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Bush Tile class
// Modified:		... 
//

#ifndef BUSH_TILE_H
#define BUSH_TILE_H

#include "Tile.h"

// This is the BushTile class that inherits from Tile 
// and creates this tile for the game
class BushTile : public Tile
{
public:
	BushTile(const char* textureName = RES_TILE_BUSH);
	virtual ~BushTile();

	//Return the type of the tile
	const char* getType();

	bool isWalkableTile();
};

#endif
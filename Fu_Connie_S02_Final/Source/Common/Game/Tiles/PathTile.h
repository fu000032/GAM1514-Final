//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Path Tile class
// Modified:		... 
//

#ifndef PATH_TILE_H
#define PATH_TILE_H

#include "Tile.h"

// This is the PathTile class that inherits from Tile 
// and creates this tile for the game
class PathTile : public Tile
{
public:
	PathTile(const char* textureName = RES_TILE_PATH);
	virtual ~PathTile();

	//Return the type of the tile
	const char* getType();
};

#endif
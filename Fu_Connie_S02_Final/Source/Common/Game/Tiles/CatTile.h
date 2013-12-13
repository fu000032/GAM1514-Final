//
// Student:			Connie Fu
// Creation Date:	Nov. 20, 2013
// Course Number:	GAME1514
// Professor:		Dan Lingman
// Purpose:			Cat Tile class
// Modified:		... 
//

#ifndef CAT_TILE_H
#define CAT_TILE_H

#include "Tile.h"

// This is the CatTile class that inherits from Tile 
// and creates this tile for the game
class CatTile : public Tile
{
public:
	CatTile(const char* textureName = RES_TILE_CAT);
	virtual ~CatTile();

	//Return the type of the tile
	const char* getType();
};

#endif
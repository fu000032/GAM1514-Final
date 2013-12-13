#include "CatTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


CatTile::CatTile(const char* textureName) : Tile(TileTypeCat, textureName, true)
{

}

CatTile::~CatTile()
{

}

const char* CatTile::getType()
{
	return TILE_CAT_TYPE;
}

#include "BushTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


BushTile::BushTile(const char* textureName) : Tile(TileTypeBush, textureName, true)
{

}

BushTile::~BushTile()
{

}

const char* BushTile::getType()
{
	return TILE_BUSH_TYPE;
}

bool BushTile::isWalkableTile()
{
	return false;
}

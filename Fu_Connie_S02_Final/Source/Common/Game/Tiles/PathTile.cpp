#include "PathTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


PathTile::PathTile(const char* textureName) : Tile(TileTypePath, textureName, true)
{

}

PathTile::~PathTile()
{

}

const char* PathTile::getType()
{
	return TILE_PATH_TYPE;
}

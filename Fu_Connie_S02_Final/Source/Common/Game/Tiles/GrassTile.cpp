#include "GrassTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


GrassTile::GrassTile(const char* textureName) : Tile(TileTypeGrass, textureName, true)
{

}

GrassTile::~GrassTile()
{

}

const char* GrassTile::getType()
{
	return TILE_GRASS_TYPE;
}

bool GrassTile::isWalkableTile()
{
	return false;
}

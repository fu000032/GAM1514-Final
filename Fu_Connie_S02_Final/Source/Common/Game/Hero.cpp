#include "Hero.h"

Hero::Hero(Level* level) : Player(level)
{

}

Hero::~Hero()
{

}

const char* Hero::getType()
{
	return HERO_TYPE;
}

void Hero::mouseLeftClickUpEvent(float positionX, float positionY)
{
	//Tile* tile = m_Level->getTileForPosition(positionX, positionY);
	//if(tile != NULL && tile->isWalkableTile() == true)
	//{
	//	// set destination tile
	//	setDestinationTile(tile);

	//	// set level's selected tile
	//	m_Level->setSelectedTileIndex(m_Level->getTileIndexForTile(tile));
	//}
}
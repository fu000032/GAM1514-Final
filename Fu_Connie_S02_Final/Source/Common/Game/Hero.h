#ifndef HERO_H
#define HERO_H

#include "Player.h"
#include "../Constants/Constants.h"
#include "Level.h"
#include "Tiles/Tile.h"

class Hero : public Player
{
public:
	Hero(Level* level);
	~Hero();

	const char* getType();

	void mouseLeftClickUpEvent(float positionX, float positionY);
};

#endif
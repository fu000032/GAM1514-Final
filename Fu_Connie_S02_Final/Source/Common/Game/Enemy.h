#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Level;

class Enemy : public Player
{
public:
	Enemy(Level* level, float speed);
	virtual ~Enemy();

	void update(double delta);
	void paint();
	void reset();

	const char* getType();
};

#endif
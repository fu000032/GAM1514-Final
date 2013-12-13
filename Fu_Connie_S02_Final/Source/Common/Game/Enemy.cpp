#include "Enemy.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../Constants/Constants.h"

Enemy::Enemy(Level* level, float speed) : Player(level)
{
	m_Speed = speed;
}

Enemy::~Enemy()
{

}

void Enemy::update(double delta)
{
	Player::update(delta);
}

void Enemy::paint()
{
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, true, 90);
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false, 90);
}

const char* Enemy::getType()
{
	return ENEMY_TYPE;
}

void Enemy::reset()
{
	Player::reset();

	// reset on proper tiles
	setDestinationTile(m_Level->getTileForIndex(g_PlayerSpawn));

	//setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
}
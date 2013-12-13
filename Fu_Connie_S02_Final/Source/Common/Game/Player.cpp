//
//  Player.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Player.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "PathNode.h"

Player::Player(Level* aLevel)
{
	//Create PathFinder object
	m_PathFinder = new PathFinder(aLevel, this);

	//Initialize the current and destination tiles to NULL
	m_CurrentTile = NULL;
	m_DestinationTile = NULL;

	//Initialize the animation member variables
	m_CanAnimate = false;
	m_AbortAnimation = false;
	m_AnimationPathNodeIndex = -1;

	m_Level = aLevel;

	// player speed
	m_Speed = PLAYER_SPEED;

	//Initialize the player's size
	setSize(PLAYER_SIZE, PLAYER_SIZE);
}

Player::~Player()
{
	if(m_PathFinder != NULL)
	{
		delete m_PathFinder;
		m_PathFinder = NULL;
	}
	//Set the current and desination tiles to NULL
	m_CurrentTile = NULL;
	m_DestinationTile = NULL;
}

void Player::update(double aDelta)
{
	if(m_PathFinder->isSearchingPath() == true)
	{
		m_PathFinder->update(aDelta);
	}

	//handle player animation
	if(isAnimating() == true && m_AnimationPathNodeIndex > -1)
	{
		PathNode* pathNode = m_PathFinder->getPathNodeAtIndex(m_AnimationPathNodeIndex);
		Tile* tile = pathNode != NULL ? pathNode->getTile() : NULL;

		//safety check that tile isn't NULL
		if(tile != NULL)
		{
			//calculate center of tile
			float centerX = tile->getX() + (tile->getWidth() - getWidth()) / 2.0f;
			float centerY = tile->getY() + (tile->getHeight() - getHeight()) / 2.0f;

			//calcualate how much player should animante use animate() to help
			float playerX = animate(getX(), centerX, aDelta);
			float playerY = animate(getY(), centerY, aDelta);
			setPosition(playerX, playerY);

			//has player reached center of tile?
			if(playerX == centerX && playerY == centerY)
			{
				m_AnimationPathNodeIndex++;

				//set current tile path flag to false
				m_CurrentTile->setIsPath(false);

				//set new current tile
				setCurrentTile(tile);

				//done animating completely?
				if(m_AnimationPathNodeIndex >= m_PathFinder->getPathSize())
				{
					stopAnimating();
					m_CurrentTile->setIsPath(false);
				}

				//is abort animation flag set?
				if(m_AbortAnimation == true)
				{
					//reset flag
					m_AbortAnimation = false;

					//begin searching for new path
					findPath();
				}
			}

		}
	}
}

void Player::paint()
{
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_INSIDE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, true, 90);
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false, 90);
}

void Player::reset()
{
	//stop animating
	stopAnimating();

	//reset path finder
	m_PathFinder->reset();

	//set destination tile to NULL
	m_DestinationTile = NULL;
}

void Player::setCurrentTile(Tile* tile)
{
	//Set the current tile pointer
	m_CurrentTile = tile;

	//Center the player's position on the tile
	setPosition(tile->getX() + ((tile->getWidth() - getWidth()) / 2), tile->getY() + ((tile->getHeight() - getHeight()) / 2));
}

void Player::setDestinationTile(Tile* tile)
{
	//Set the destination tile pointer
	m_DestinationTile = tile;

	//start pathfinding
	if(isAnimating() == false)
	{
		findPath();
	}
	else
	{
		m_AbortAnimation = true;
	}
}

void Player::pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound)
{
	if(pathFinder == m_PathFinder)
	{
		if(pathWasFound == true)
		{
			startAnimating();
		}
		else
		{
			m_PathFinder->reset();
		}
	}
}

PathFinder* Player::getPathFinder()
{
	return m_PathFinder;
}

void Player::findPath()
{
	m_PathFinder->reset();
	m_PathFinder->findPath(m_CurrentTile, m_DestinationTile);
}

float Player::animate(float aCurrent, float aTarget, double aDelta)
{
	float increment = aDelta * PLAYER_SPEED * (aTarget < aCurrent ? -1 : 1);
	if(fabs(increment) > fabs(aTarget - aCurrent))
	{
		return aTarget;
	}
	else
	{
		aCurrent += increment;
	}
	return aCurrent;
}

void Player::startAnimating()
{
	m_CanAnimate = true;
	m_AnimationPathNodeIndex = 0;
}

void Player::stopAnimating()
{
	m_CanAnimate = false;
	m_AnimationPathNodeIndex = -1;
}

bool Player::isAnimating()
{
	return m_CanAnimate;
}

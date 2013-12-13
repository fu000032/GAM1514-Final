#ifndef PATHNODE_H
#define PATHNODE_H

#include "../OpenGL/OpenGL.h"
#include "Tiles/Tile.h"
#include <stdlib.h>

class Tile;

class PathNode
{
public:
	PathNode(Tile* tile);
	~PathNode();

	void paintScore(OpenGLColor color);

	Tile* getTile();

	int getScoreG();
	int getScoreF();
	int getScoreH();

	PathNode* getParentNode();

	void setScoreG(int scoreG);
	void setScoreH(int scoreH);
	
	void setParentNode(PathNode* parentNode);

	static bool compareNodes(PathNode* nodeA, PathNode* nodeB);

private:
	Tile* m_Tile;
	int m_ScoreG;
	int m_ScoreH;
	PathNode* m_ParentNode;
};

#endif
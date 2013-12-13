#include "PathFinder.h"
#include "PathNode.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>

PathFinder::PathFinder(Level* level, PathFinderListener* listener) :
    m_Level(level),
    m_Listener(listener),
    m_State(StateIdle),
    m_DestinationTileIndex(-1),
    m_SearchDelay(0.0),
    m_EnableSearchDelay(false)
{

}

PathFinder::~PathFinder()
{
    clearPathNodes();
}

void PathFinder::findPath(Tile* aCurrentTile, Tile* aDestinationTile)
{
    //Safety check that the state is Idle, if not, then path already found/ in process of being found
	if(m_State != StateIdle)
	{
		return;
	}

	//Cycle through and reset all tile path flags to false
	for(int i = 0; i < m_Level->getNumberOfTiles(); i++)
	{
		Tile* tile = m_Level->getTileForIndex(i);
		if(tile != NULL && tile->isWalkableTile() == true)
		{
			tile->setIsPath(false);
		}
	}

	//Clear path nodes
	clearPathNodes();

	//Get current tile index and destination tiles
	int currentTileIndex = m_Level->getTileIndexForTile(aCurrentTile);
	m_DestinationTileIndex = m_Level->getTileIndexForTile(aDestinationTile);

	//Safety check that tile and destination tile aren't the same
	if(currentTileIndex == m_DestinationTileIndex)
	{
		return;
	}

	//Make sure destination tile is walkable
	if(aDestinationTile->isWalkableTile() == false)
	{
		return;
	}

	//Allocate current tile path node and add to open list (vector)
	PathNode* pathNode = new PathNode(aCurrentTile);
	addPathNodeToOpenList(pathNode);

	//Set state to searching
	m_State = StateSearchingPath;

	//Set search delay to 0
	m_SearchDelay = 0.0;

}

void PathFinder::update(double aDelta)
{
    if(m_SearchDelay > 0.0)
    {
        m_SearchDelay -= aDelta;
        if(m_SearchDelay <= 0.0)
        {
            m_SearchDelay = 0.0;
        }
        return;
    }
    
    
    //Check for state searching
	while(isSearchingPath() == true && m_DestinationTileIndex != -1)
	{
		//Safety check that there is something in open list vector
		if(m_PathNodeOpen.size() == 0)
		{
			// set state to error
			m_State = StateError;

			// notify listener
			if(m_Listener != NULL)
			{
				m_Listener->pathFinderFinishedSearching(this, false);
			}

			return;
		}

		//Get node with lowest F score from open list (because it's sorted, it should be first element
		PathNode* currentNode = m_PathNodeOpen.front();

		//Add node to the closed list and remove from open list
		m_PathNodeClosed.push_back(currentNode);
		m_PathNodeOpen.erase(m_PathNodeOpen.begin());

		//Check if node is at destination tile
		//If at destination tile, stop searching and build final path
		int currentNodeTileIndex = m_Level->getTileIndexForTile(currentNode->getTile());
		if(currentNodeTileIndex == m_DestinationTileIndex)
		{
			// Build final node path, will use current node's parents to track back from destination
			buildFinalNodePath(currentNode);

			// set state to Path found
			m_State = StateFoundPath;

			// notify listener
			if(m_Listener != NULL)
			{
				m_Listener->pathFinderFinishedSearching(this, true);
			}

			return;
		}

		//If not, get adjacent tiles from node and add to the open list
		std::vector<Tile*> adjacentTiles;

		//Check surrounding tiles for walkable (above, below, left, right)
		addAdjacentTile(adjacentTiles, currentNode->getTile(), 0, -1); // above
		addAdjacentTile(adjacentTiles, currentNode->getTile(), 0, 1 ); // below
		addAdjacentTile(adjacentTiles, currentNode->getTile(), -1, 0); // left
		addAdjacentTile(adjacentTiles, currentNode->getTile(), 1, 0 ); // right

		//Cycle through adjacent tiles that are walkable 
		for(int i = 0; i < adjacentTiles.size(); i++)
		{
			Tile* adjacentTile = adjacentTiles.at(i);
			//Does tile exist already in closed list
			if(doesTileExistInClosedList(adjacentTile) == true)
			{
				//If yes, ignore it
				continue;
			}
			//Does tile exist in open list
			if(doesTileExistInOpenList(adjacentTile) == false)
			{
				//If no, create new path node for it
				PathNode* adjacentNode = new PathNode(adjacentTile);
					//Set parent node
				adjacentNode->setParentNode(currentNode);
					//Calculate G and H scores
				adjacentNode->setScoreG(currentNode->getScoreG() + 1);
				Tile* destinationTile = m_Level->getTileForIndex(m_DestinationTileIndex);
				int scoreH = getManhattanDistanceCost(adjacentTile, destinationTile);
				adjacentNode->setScoreH(scoreH);
					//Add tile to open list and sort
				addPathNodeToOpenList(adjacentNode);
			}
			else
			{
				//If yes, compare scores and keep lowest F score tile
				PathNode* existingNode = getOpenPathNodeForTile(adjacentTile);
					//If tile has lower F score, update the G score and update parent node
				if(currentNode->getScoreG() + 1 < existingNode->getScoreG())
				{
					existingNode->setScoreG(currentNode->getScoreG() + 1);
					existingNode->setParentNode(currentNode);

					//Sort open list
					sortOpenList();
				}	
			}
		}
	}
    
    
    //If the search delay is enabled, set the delay timer
    if(m_EnableSearchDelay == true)
    {
        m_SearchDelay = PATH_FINDING_DELAY;
    }
}

void PathFinder::paint()
{
    //Paint the open list path scoring
    for(int i = 0; i < m_PathNodeOpen.size(); i++)
    {
        m_PathNodeOpen.at(i)->paintScore(OpenGLColorRed());
    }
    
    //Paint the closed list path scoring
    for(int i = 0; i < m_PathNodeClosed.size(); i++)
    {
        m_PathNodeClosed.at(i)->paintScore(OpenGLColorBlue());
    }
    
    //Paint the final path scoring
    for(int i = 0; i < m_PathNodeFinal.size(); i++)
    {
        m_PathNodeFinal.at(i)->paintScore(OpenGLColorYellow());
    }
}

void PathFinder::reset()
{
    m_State = StateIdle;
}

void PathFinder::addAdjacentTile(std::vector<Tile*>& aAdjacentTiles, Tile* aCurrentTile, int aDeltaX, int aDeltaY)
{
	int adjacentCoordinateX = m_Level->getTileCoordinateForPositionX(aCurrentTile->getX()) + aDeltaX;
	int adjacentCoordinateY = m_Level->getTileCoordinateForPositionY(aCurrentTile->getY()) + aDeltaY;

	Tile* adjacentTile = m_Level->getTileForCoordinates(adjacentCoordinateX, adjacentCoordinateY);
	if(adjacentTile!=NULL)
	{
		// is tile walkable and not outside level
		bool isWalkable = adjacentTile->isWalkableTile();
		bool isValid = m_Level->validateTileCoordinates(adjacentCoordinateX, adjacentCoordinateY);

		if(isWalkable == true && isValid == true)
		{
			aAdjacentTiles.push_back(adjacentTile);
		}
	}
}

bool PathFinder::doesTileExistInClosedList(Tile* aTile)
{
    //Get the tile index from the level for the tile pointer
    int tileIndex = m_Level->getTileIndexForTile(aTile);
    
    //Cycle through the closed list and compare the tile indexes
    for(int i = 0; i < m_PathNodeClosed.size(); i++)
    {
        PathNode* pathNode = m_PathNodeClosed.at(i);
        if(m_Level->getTileIndexForTile(pathNode->getTile()) == tileIndex)
        {
            return true;
        }
    }
    
    //The tile doesn't exist in the closed list
    return false;
}

bool PathFinder::doesTileExistInOpenList(Tile* aTile)
{
    return getOpenPathNodeForTile(aTile) != NULL;
}

PathNode* PathFinder::getOpenPathNodeForTile(Tile* aTile)
{
    //Get the tile index from the level for the tile pointer
    int tileIndex = m_Level->getTileIndexForTile(aTile);
    
    //Cycle through the open list and compare the tile indexes
    for(int i = 0; i < m_PathNodeOpen.size(); i++)
    {
        PathNode* pathNode = m_PathNodeOpen.at(i);
        if(m_Level->getTileIndexForTile(pathNode->getTile()) == tileIndex)
        {
            return pathNode;
        }
    }
    
    //The tile doesn't exist in the open list, return NULL
    return NULL;
}

bool PathFinder::isSearchingPath()
{
    return m_State == StateSearchingPath;
}

int PathFinder::getPathSize()
{
    return m_PathNodeFinal.size();
}

void PathFinder::sortOpenList()
{
	std::sort(m_PathNodeOpen.begin(), m_PathNodeOpen.end(), PathNode::compareNodes);
	//note: compareNodes returns a bool that is true if the first node's F score is smaller than the second's
}

PathNode* PathFinder::getPathNodeAtIndex(int aIndex)
{
    if(aIndex >= 0 && aIndex < getPathSize())
    {
        return m_PathNodeFinal.at(aIndex);
    }
    return NULL;
}

void PathFinder::addPathNodeToOpenList(PathNode* aPathNode)
{
	//Insert the Path node into the Open path node vector
	m_PathNodeOpen.push_back(aPathNode);
    
    //Sort the open list
    sortOpenList();
}

void PathFinder::buildFinalNodePath(PathNode* aPathNode)
{
	do
	{
        //Safety check the parentNode
		if(aPathNode->getParentNode() != NULL)
		{
			m_PathNodeFinal.insert(m_PathNodeFinal.begin(), aPathNode);
		}
        
		//Set the tile path flag to true
		aPathNode->getTile()->setIsPath(true);
        
		//Set the path node's pointer to it's parent
		aPathNode = aPathNode->getParentNode();
	}
	while (aPathNode != NULL);
}

void PathFinder::clearPathNodes()
{
	//Now cycle through the Open node path vector, and delete all the path node
	while(m_PathNodeOpen.size() > 0)
	{
		//Get the last element in the vector
		PathNode* node = m_PathNodeOpen.back();
        
		//Delete the path node
		delete node;
        
		//Remove the last element in the vector
		m_PathNodeOpen.pop_back();
	}
    
	//Lastly cycle through the Closed node path vector, and delete all the path node
	while(m_PathNodeClosed.size() > 0)
	{
		//Get the last element in the vector
		PathNode* node = m_PathNodeClosed.back();
        
		//Delete the path node
		delete node;
        
		//Remove the last element in the vector
		m_PathNodeClosed.pop_back();
	}
    
    //Clear the final path node list
    m_PathNodeFinal.clear();
    
    //Reset the destination tile index
    m_DestinationTileIndex = -1;
}

void PathFinder::togglePathFindingDelay()
{
    m_EnableSearchDelay = !m_EnableSearchDelay;
}

int PathFinder::getManhattanDistanceCost(Tile* aStartTile, Tile* aDestinationTile)
{
	//Here we use the Manhattan method, which calculates the total number of step moved horizontally and vertically to reach the
	//final desired step from the current step, ignoring any obstacles that may be in the way
	int distance = abs(m_Level->getTileCoordinateForPositionX(aDestinationTile->getX()) - m_Level->getTileCoordinateForPositionX(aStartTile->getX())) 
    + abs(m_Level->getTileCoordinateForPositionY(aDestinationTile->getY()) - m_Level->getTileCoordinateForPositionY(aStartTile->getY()));
    
    //Return the distance between the two tiles
	return distance;
}
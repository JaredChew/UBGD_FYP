#pragma once

#include <vector>
#include <utility> 
#include <queue>

class PathNode;

class PathFinder {

private:

	std::vector< std::vector<PathNode> > &grid;

public:

	enum class SearchType { DIJKSTRA, A_STAR };

private:

	enum class DiagonalDirection { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };
	enum class DirectionCost { HORIVERTI_COST = 10, DIAGONAL_COST = 14 };

	SearchType searchType;

	int tilesWidth;
	int tilesHeight;

	int startNodeX;
	int startNodeY;

	int endNodeX;
	int endNodeY;

	bool isPathFound;
	bool allowDiagonal;
	bool allowCrossCorners;

	bool isCornerPossible[4];
	//BitData8 isCornerPossible;

	std::pair<int, int> nextPath;

	std::vector<std::pair<int, int>> toCheck;
	std::vector<std::pair<int, int>> searchList;

	std::vector<std::pair<int, int>> path; //stack alternative? - if dont want history

	std::queue<std::pair<int, int>> previouslySearched;

private:

	int calculateNodeTraversal(int x, int y);

	bool isAtDestination();
	bool possiblePassthrough(const int &x, const int &y);

	void getNextPath(const int &x, const int &y);

	void searchPath();
	void evaluateNextPath();

	void updateSearchList();
	void updateCrossCorner(const int &direction);
	void updateNeighbourNode(const int &x, const int &y);

	void setCost();
	void setParent(const int &x, const int &y);
	void setPathToDestination(const int &x, const int &y);

public:

	PathFinder(std::vector< std::vector<PathNode> > &grid, PathNode start, PathNode end, const bool &allowDiagonal, const bool &allowCrossCorners, const SearchType &searchType);
	~PathFinder();

	//void reset();

	void searchCotinuous();
	void searchStepByStep();

	bool getIsPathFound();

	std::vector<std::pair<int, int>> getPath();
	std::queue<std::pair<int, int>> &getPreviouslySearched();

};
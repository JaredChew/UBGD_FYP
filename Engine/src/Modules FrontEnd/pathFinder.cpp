#include "pathFinder.h"

#include "PathNode.h"

PathFinder::PathFinder(std::vector< std::vector<PathNode> > &grid, PathNode start, PathNode end,
					   const bool &allowDiagonal, const bool &allowCrossCorners, const SearchType &searchType) : grid(grid) {

	tilesWidth = grid.size();
	tilesHeight = grid[0].size();

	startNodeX = start.getX();
	startNodeY = start.getY();

	endNodeX = end.getX();
	endNodeY = end.getY();

	grid[startNodeX][startNodeY].setOpenNode(false);

	nextPath = std::make_pair(startNodeX, startNodeY);

	this->searchType = searchType;

	isPathFound = false;

	this->allowDiagonal = allowDiagonal;
	this->allowCrossCorners = allowDiagonal && allowCrossCorners;

}

PathFinder::~PathFinder() { }

bool PathFinder::possiblePassthrough(const int &x, const int &y) {

	if (x < 0 || x >= tilesWidth) { return false; }
	if (y < 0 || y >= tilesHeight) { return false; }

	if (!grid[x][y].isNodeOpen()) { return false; }
	if (!grid[x][y].isOrphan()) { return false; }

	if (grid[x][y].isVisited()) { return false; }

	return true;

}

void PathFinder::updateCrossCorner(const int &direction) {

	if (allowCrossCorners) { return; }

	isCornerPossible[direction] = false;

}

void PathFinder::getNextPath(const int &x, const int &y) {

	//up down
	if (possiblePassthrough(x, y - 1)) { toCheck.emplace_back(x, y - 1); }
	else { updateCrossCorner((int)DiagonalDirection::NORTH_WEST); updateCrossCorner((int)DiagonalDirection::NORTH_EAST); }
	if (possiblePassthrough(x, y + 1)) { toCheck.emplace_back(x, y + 1); }
	else { updateCrossCorner((int)DiagonalDirection::SOUTH_WEST); updateCrossCorner((int)DiagonalDirection::SOUTH_EAST); }

//left right
	if (possiblePassthrough(x + 1, y)) { toCheck.emplace_back(x + 1, y); }
	else { updateCrossCorner((int)DiagonalDirection::NORTH_EAST); updateCrossCorner((int)DiagonalDirection::SOUTH_EAST); }
	if (possiblePassthrough(x - 1, y)) { toCheck.emplace_back(x - 1, y); }
	else { updateCrossCorner((int)DiagonalDirection::NORTH_WEST); updateCrossCorner((int)DiagonalDirection::SOUTH_WEST); }

	if (!allowDiagonal) { return; }

	//diagonal left
	if (possiblePassthrough(x - 1, y - 1) && isCornerPossible[(int)DiagonalDirection::NORTH_WEST]) { toCheck.emplace_back(x - 1, y - 1); }
	if (possiblePassthrough(x - 1, y + 1) && isCornerPossible[(int)DiagonalDirection::SOUTH_WEST]) { toCheck.emplace_back(x - 1, y + 1); }

	//diagonal right
	if (possiblePassthrough(x + 1, y - 1) && isCornerPossible[(int)DiagonalDirection::NORTH_EAST]) { toCheck.emplace_back(x + 1, y - 1); }
	if (possiblePassthrough(x + 1, y + 1) && isCornerPossible[(int)DiagonalDirection::SOUTH_EAST]) { toCheck.emplace_back(x + 1, y + 1); }

}

void PathFinder::setPathToDestination(const int &x, const int &y) {

	path.push_back(std::make_pair(x, y));

	if (grid[x][y].getX() != startNodeX || grid[x][y].getY() != startNodeY) {
		setPathToDestination(grid[x][y].getParent()->getX(), grid[x][y].getParent()->getY());
	}

}

void PathFinder::setParent(const int &x, const int &y) {

	for (int i = 0; i < toCheck.size(); ++i) {

		grid[toCheck[i].first][toCheck[i].second].setParent(&grid[x][y]);

	}

}

bool PathFinder::isAtDestination() {

	for (int i = 0; i < toCheck.size(); ++i) {
		if (toCheck[i].first == endNodeX && toCheck[i].second == endNodeY) {

			nextPath = std::make_pair(toCheck[i].first, toCheck[i].second);

			return true;

		}

	}

	return false;

}

int PathFinder::calculateNodeTraversal(int x, int y) {

	int parentCounter = 0;

	PathNode *node = &grid[x][y];

	while (node->getParent() != nullptr) {

		++parentCounter;

		node = node->getParent();

	}

	return parentCounter;

}

void PathFinder::updateNeighbourNode(const int &x, const int &y) {

	int parent_gCost = 0;
	int hCost = 0, gCost = 0, fCost = 0;

	for (int i = 0; i < searchList.size(); ++i) {

		if (searchList[i].first < x - 1 || searchList[i].first > x + 1) { continue; }
		if (searchList[i].second < y - 1 || searchList[i].second > y + 1) { continue; }

		parent_gCost = grid[searchList[i].first][searchList[i].second].getParent()->get_gCost();

		if (!abs(searchList[i].first - startNodeX) || !abs(searchList[i].second - startNodeY)) { gCost = parent_gCost + (int)DirectionCost::HORIVERTI_COST; }
		else { gCost = parent_gCost + (int)DirectionCost::DIAGONAL_COST; }

		if (gCost >= parent_gCost) { continue; }

		hCost = abs(endNodeX - searchList[i].first) + abs(endNodeY - searchList[i].second);

		grid[searchList[i].first][searchList[i].second].setParent(&grid[x][y]);

		grid[searchList[i].first][searchList[i].second].set_gCost(gCost);

		if (searchType == SearchType::A_STAR) { grid[searchList[i].first][searchList[i].second].set_hCost(hCost); }

	}

}

void PathFinder::setCost() {

	for (int i = 0, parentCounter = 0; i < toCheck.size(); ++i) {

		parentCounter = calculateNodeTraversal(toCheck[i].first, toCheck[i].second);

		if (!abs(toCheck[i].first - startNodeX) || !abs(toCheck[i].second - startNodeY)) {
			grid[toCheck[i].first][toCheck[i].second].set_gCost(parentCounter * (int)DirectionCost::HORIVERTI_COST);
		}
		else {
			grid[toCheck[i].first][toCheck[i].second].set_gCost(parentCounter * (int)DirectionCost::DIAGONAL_COST);
		}

		if (searchType == SearchType::A_STAR) {
			grid[toCheck[i].first][toCheck[i].second].set_hCost(abs(endNodeX - toCheck[i].first) + abs(endNodeY - toCheck[i].second));
		}

	}

}

void PathFinder::updateSearchList() {

	previouslySearched = { };

	for (int i = 0; i < toCheck.size(); ++i) {

		searchList.emplace_back(toCheck[i].first, toCheck[i].second);
		previouslySearched.emplace(toCheck[i].first, toCheck[i].second);

	}

	toCheck.clear();

}

void PathFinder::evaluateNextPath() {

	unsigned int lowestCost = ~0;

	int index = 0;

	for (int i = 0, fCost = 0; i < searchList.size(); ++i) {

		fCost = grid[searchList[i].first][searchList[i].second].get_fCost();

		if (fCost < lowestCost) {

			lowestCost = fCost;

			index = i;

		}

	}

	grid[searchList[index].first][searchList[index].second].setVisited(true);

	nextPath = std::make_pair(searchList[index].first, searchList[index].second);

	searchList[index] = std::move(searchList.back());
	searchList.pop_back();

}

void PathFinder::searchPath() {

	for (int i = 0; i < 4; ++i) { isCornerPossible[i] = true; }

	getNextPath(nextPath.first, nextPath.second);

	setParent(nextPath.first, nextPath.second);

	updateNeighbourNode(nextPath.first, nextPath.second);

	if (isAtDestination()) {

		isPathFound = true;

		setPathToDestination(nextPath.first, nextPath.second);

		return;

	}

	setCost();

	updateSearchList();

	evaluateNextPath();

	if (searchList.empty()) { isPathFound = true; }

}

void PathFinder::searchCotinuous() {

	while (!isPathFound) { searchPath(); }

}

void PathFinder::searchStepByStep() {

	if (isPathFound) { return; }

	searchPath();

}

bool PathFinder::getIsPathFound() {
	return isPathFound;
}

std::vector<std::pair<int, int>> PathFinder::getPath() {
	return path;
}

std::queue<std::pair<int, int>> &PathFinder::getPreviouslySearched() {
	return previouslySearched;
}
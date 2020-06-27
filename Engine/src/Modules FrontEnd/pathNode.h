#pragma once

class PathNode {

private:

	PathNode *parent;

	bool visited;
	bool openNode;

	int weight;

	int gCost;
	int hCost;

	int x;
	int y;

public:

	PathNode(const int &x = 0, const int &y = 0, const int &weight = 1, const bool &openNode = true);
	~PathNode();

	void resetStatus();

	void setParent(PathNode *parent);
	void setWeight(const int &weight);
	void setVisited(const bool &visited);
	void setOpenNode(const bool &openNode);

	void set_gCost(const int &gCost);
	void set_hCost(const int &hCost);

	void setX(const int &x);
	void setY(const int &y);

	PathNode *getParent();

	bool isNodeOpen();
	bool isVisited();
	bool isOrphan();

	int getWeight();
	int get_hCost();
	int get_gCost();
	int get_fCost();

	int getX();
	int getY();

};
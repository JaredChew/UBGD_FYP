#include "pathNode.h"

PathNode::PathNode(const int &x, const int &y, const int &weight, const bool &openNode) {

	this->openNode = openNode;

	this->weight = weight;

	gCost = 0;
	hCost = 0;

	this->x = x;
	this->y = y;

	visited = false;

	parent = nullptr;

}

PathNode::~PathNode() { }

void PathNode::resetStatus() {

	gCost = 0;
	hCost = 0;

	visited = false;

	parent = nullptr;

}

void PathNode::setVisited(const bool &visited) {
	this->visited = visited;
}

void PathNode::setParent(PathNode *parent) {
	this->parent = parent;
}

void PathNode::setWeight(const int &weight) {
	this->weight = weight;
}

void PathNode::set_hCost(const int &hCost) {
	this->hCost = hCost * weight;
}

void PathNode::set_gCost(const int &gCost) {
	this->gCost = gCost;
}

void PathNode::setOpenNode(const bool &openNode) {
	this->openNode = openNode;
}

void PathNode::setX(const int &x) {
	this->x = x;
}

void PathNode::setY(const int &y) {
	this->y = y;
}

bool PathNode::isNodeOpen() {
	return openNode;
}

bool PathNode::isVisited() {
	return visited;
}

PathNode *PathNode::getParent() {
	return parent;
}

bool PathNode::isOrphan() {
	return parent == nullptr;
}

int PathNode::getWeight() {
	return weight;
}

int PathNode::get_gCost() {
	return gCost;
}

int PathNode::get_hCost() {
	return hCost;
}

int PathNode::get_fCost() {
	return hCost + gCost;
}

int PathNode::getX() {
	return x;
}

int PathNode::getY() {
	return y;
}

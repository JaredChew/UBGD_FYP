#pragma once

template <typename dataType>
class Node2D {

private:

	dataType value;

	Node2D<dataType> *leftNode;
	Node2D<dataType> *rightNode;

public:

	Node2D() :leftNode(nullptr), rightNode(nullptr) {

		value = NULL;

	}

	Node2D(dataType value) :leftNode(nullptr), rightNode(nullptr) {

		value = NULL;

	}

	Node2D(dataType value, Node2D<dataType> *leftNode, Node2D<dataType> *rightNode) : leftNode(leftNode), rightNode(rightNode) {

		this->value = value;

	}

	~Node2D() {

		if (!leftNode) { delete leftNode; }
		if (!rightNode) { delete rightNode; }

	}

	void setValue(const dataType &value) { this->value = value; }

	void setLeftNode(Node2D<dataType> *&leftNode) { this->leftNode = leftNode; }

	void setRightNode(Node2D<dataType> *&rightNode) { this->rightNode = rightNode; }

	dataType getValue() const { return value; }

	Node2D *&getLeftNode() { return leftNode; }

	Node2D *&getRightNode() { return rightNode; }

};
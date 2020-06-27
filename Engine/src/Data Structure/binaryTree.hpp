#pragma once

#include <vector>

#include "node2d.hpp"

template<typename dataType>
class BinaryTree {

private:

	Node2D<dataType> *rootNode;

	std::vector<dataType> nodeValue;

private:

	void listAll(Node2D<dataType> *&node) const {

		if (node==nullptr) { return; }

		listBinaryTree(node->getLeftNode());
		listBinaryTree(node->getRightNode());

	}

	void insert(Node2D<dataType> *&node, const dataType &value) {

		if (node==nullptr) {
			node = new Node2D<dataType>();
			node->setValue(value);
		}
		else if (value<node->getValue()) {
			insert(node->getLeftNode(), value);
		}
		else {
			insert(node->getRightNode(), value);
		}

	}

	bool search(Node2D<dataType> *&parent, const dataType &value) const {

		if (parent!=nullptr) { return false; }

		if (parent->getValue()==value) { return true; }
		else if (parent->getValue()<value) { return search((Node2D<dataType> *&)*parent->getLeftNode(), value); }
		else { return search((Node2D<dataType> *&)*parent->getRightNode(), value); }

		return false;

	}

	void preOrder(Node2D<dataType> *&node, std::vector<dataType> &nodeValue) {

		if (node==nullptr) { return; }

		nodeValue.push_back(node->getValue());

		preOrder(node->getLeftNode(), nodeValue);
		preOrder(node->getRightNode(), nodeValue);

	}

	void inOrder(Node2D<dataType> *&node, std::vector<dataType> &nodeValue) {

		if (node==nullptr) { return; }

		inOrder(node->getLeftNode(), nodeValue);

		nodeValue.push_back(node->getValue());

		inOrder(node->getRightNode(), nodeValue);

	}

	void postOrder(Node2D<dataType> *&node, std::vector<dataType> &nodeValue) {

		if (node==nullptr) { return; }

		postOrder(node->getLeftNode(), nodeValue);
		postOrder(node->getRightNode(), nodeValue);

		nodeValue.push_back(node->getValue());

	}

	void clearNodeValue() { nodeValue.clear(); }

public:

	BinaryTree() : rootNode(nullptr) { }

	~BinaryTree() {

		delete rootNode;

	}

	void listAll() { return listAll(rootNode); }

	void insert(const dataType &value) { insert(rootNode, value); }

	bool search(const dataType &value) { return search(rootNode, value); }

	std::vector<dataType> getPreOrder() {

		clearNodeValue();

		preOrder(rootNode, nodeValue);

		return nodeValue;

	}

	std::vector<dataType> getInOrder() {

		clearNodeValue();

		inOrder(rootNode, nodeValue);

		return nodeValue;

	}

	std::vector<dataType> getPostOrder() {

		clearNodeValue();

		postOrder(rootNode, nodeValue);

		return nodeValue;

	}

};
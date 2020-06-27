#pragma once

#include "node2D.hpp"

template<typename dataType>
class DoubleLinkedList {

private:

	Node2D<dataType> *start;

public:

	DoubleLinkedList() : start(nullptr) { }

	~DoubleLinkedList() {

		delete start;
		start = nullptr;

	}

	void pushFront(int value) {

		start->setLeftNode(new Node2D<dataType>(value));

		start->getLeftNode()->setRightNode(start);

		start = start->getLeftNode();

	}

	void pushBack(int value) {

		Node2D<dataType> *current = start;
		Node2D<dataType> *previous = nullptr;

		bool isAdded = false;

		do {

			if (current==nullptr) {

				current = new Node2D<dataType>(value);

				isAdded = true;

				if (previous!=nullptr) {
					current->getLeftNode() = previous;
					current->getLeftNode()->setRightNode(current);
				}

				if (start==nullptr) {
					start = current;
				}

			}
			else {

				previous = current;
				current = current->getRightNode();

			}

		}
		while (!isAdded);

	}

	void pushAtLocation(int value, int location) {

		Node2D<dataType> *current = getNodeWithValueOf(location);

		if (current==nullptr) { return; }

		Node2D<dataType> *newNode = new Node2D<dataType>(value);

		current->getLeftNode()->setRightNode(newNode);
		newNode->getLeftNode() = current->getLeftNode();
		newNode->setRightNode(current);
		current->setLeftNode(newNode);

	}

	void popBack() {

		Node2D<dataType> *current = start;
		Node2D<dataType> *previous = nullptr;

		bool isRemoved = false;

		do {

			if (current==nullptr) {

				previous->getLeftNode()->setRightNode(nullptr);

				delete previous;
				previous = nullptr;

				isRemoved = true;

			}
			else {

				previous = current;
				current = current->getRightNode();

			}

		}
		while (!isRemoved);

	}

	void popAtLocation(int location) {

		Node2D<dataType> *current = getNodeWithValueOf(location);

		if (current->value!=location) { return; }

		current->getLeftNode()->setRightNode(current->getRightNode());
		current->getRightNode()->setLeftNode(current->getLeftNode());

		current->setRightNode(nullptr);
		current->setLeftNode(nullptr);

		delete current;
		current = nullptr;

	}

	void popFront() {

		Node2D<dataType> *nextNodeAddress = start->getRightNode();

		start->getRightNode()->setLeftNode(nullptr);

		start->setRightNode(nullptr);

		delete start;
		start = nullptr;

		start = nextNodeAddress;

	}

	Node2D<dataType> *getNodeWithValueOf(dataType value) {

		Node2D<dataType> *current = start;

		while (current!=nullptr) {

			if (current->getValue()==value) {

				return current;

			}

			current = current->getRightNode();

		}

		return nullptr;

	}

};
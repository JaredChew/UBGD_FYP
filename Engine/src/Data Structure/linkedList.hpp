#pragma once

template<typename dataType>
class LinkedList {

private:

	int index;

public:

	LinkedList *next;

	dataType data;

public:

	LinkedList() : next(nullptr) {

		index = 0;

	}

	~LinkedList() { }

	LinkedList<dataType> *get(const int &index) {

		LinkedList<dataType> *temp = next;

		while (temp->next!=nullptr) {

			if (temp->getIndex()==index) { return temp; }

			temp = next->next;

		}

		return nullptr;

	}

	void push(const dataType &data, const int &index) {

		if (next==nullptr) {

			next = new LinkedList();

			next->setIndex(index);
			next->data = data;

			return;

		}

		LinkedList<dataType> *temp = next;

		while (temp->next!=nullptr) {
			temp = next->next;
		}

		temp = new LinkedList();

		temp->setIndex(index);
		temp->data = data;

	}

	void pushAt(dataType data, const int &index) {

		LinkedList<dataType> *temp = next;

		while (temp!=nullptr||temp->next!=nullptr) {

			if (temp->next->getIndex()==index) {

				LinkedList *nodePointer = temp->next;

				temp->next = new LinkedList();

				temp->next->setIndex(index);
				temp->data = data;

				temp->next->next = nodePointer;

				return;

			}

			temp = next->next;

		}

	}

	void pop() {

		LinkedList<dataType> *temp = next;

		while (temp->next->next!=nullptr&&temp->next!=nullptr) {

			temp = next->next;
		}

		delete temp->next;
		temp->next = nullptr;

	}

	void popAt(const int &index) {

		LinkedList<dataType> *temp = next;

		while (temp->next!=nullptr) {

			if (temp->next->getIndex()==index) {

				LinkedList *nodePointer = temp->next->next;

				temp->next->next = nullptr;

				delete temp->next;
				temp->next = nodePointer;

				return;
			}

		}

	}

	void setIndex(const int &index) { this->index = index; }

	int getIndex() { return index; }

};
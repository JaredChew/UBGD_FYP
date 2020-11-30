#pragma once


template<typename DataType>
class DoubleLinkList {

private:

	class Node
	{
		DataType data;
		Node* previous;
		Node* next;

		friend class DoubleLinkList;
	};

public:

	class iterator {
	private:
		const Node* _currentNode;

	public:
		iterator() noexcept : _currentNode(_head) { }
		iterator(const Node* node) noexcept : _currentNode(node) { }
		iterator& operator=(Node* node)
		{
			_currentNode = node;
			return *this;
		}
		// Prefix
		DoubleLinkList<DataType>::iterator& operator++()
		{
			if (_currentNode)
				_currentNode = _currentNode->next;
			return *this;
		}
		// Postfix
		DoubleLinkList<DataType>::iterator operator++(int)
		{
			DoubleLinkList<DataType>::iterator iter = *this;
			++* this;
			return iter;
		}
		bool operator!=(const DoubleLinkList<DataType>::iterator& iterator)
		{
			return _currentNode != iterator._currentNode;
		}
		DataType operator*()
		{
			return _currentNode->data;
		}
	};

private:

	Node* _head, * _tail;

	int _size;

public:

	DoubleLinkList() noexcept {

		_head = nullptr;
		_tail = nullptr;
		_size = 0;

	}

	~DoubleLinkList() {

		if (_head == nullptr) return;

		Node* cur = _head;
		Node* temp = _head->next;


		for (size_t i = 0; i < _size; i++)
		{
			delete cur;
			cur = temp;
			if (temp != nullptr)
			{
				temp = temp->next;
			}
		}

		_head = _tail = nullptr;

	}

	iterator begin()
	{
		return iterator(_head);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	void push_back(DataType data) {

		Node* temp = new Node();
		temp->data = data;
		temp->previous = nullptr;
		temp->next = nullptr;

		if (_head == nullptr)
		{
			_head = temp;
			_tail = temp;
		}
		else
		{
			_tail->next = temp;
			temp->previous = _tail;
			_tail = temp;
		}

		_size++;

	}

	void push_front(DataType data) {

		Node* temp = new Node();
		temp->data = data;
		temp->previous = nullptr;
		temp->next = nullptr;

		if (_head == nullptr)
		{
			_head = temp;
			_tail = temp;
		}
		else
		{
			temp->next = _head;
			_head->previous = temp;
			_head = temp;
		}

		_size++;

	}

	void insert(Node* node, DataType data)
	{
		if (node == nullptr) return;

		Node* pre = node->previous;
		Node* cur = node;
		Node* temp = new Node();

		temp->data = data;
		temp->previous = cur->previous;
		temp->next = cur;
		pre->next = temp;
		cur->previous = temp;

		_size++;

	}

	void insert(int index, DataType data)
	{

		if (index < 0 || index >= _size) return;

		Node* pre = nullptr;
		Node* cur = _head;

		size_t i = 0;
		while (i < index) {

			pre = cur;
			cur = cur->next;

			i++;

		}

		Node* temp = new Node();
		if (pre == nullptr)
		{
			temp->data = data;
			temp->previous = nullptr;
			temp->next = cur;
			if (cur != nullptr)
			{
				cur->previous = temp;
				_head = temp;
			}
			else
			{
				_head = temp;
				_tail = temp;
			}
		}
		else
		{
			temp->data = data;
			temp->previous = pre;
			temp->next = cur;
			pre->next = temp;
			cur->previous = temp;
		}

		_size++;

	}

	void pop_front() {

		if (_head == nullptr) return;

		Node* temp = _head;
		_head = _head->next;
		_head->previous = nullptr;

		_size--;
		delete temp;

	}

	void pop_back() {

		if (_tail == nullptr) return;

		Node* temp = _tail;
		_tail = _tail->previous;
		_tail->next = nullptr;

		_size--;
		delete temp;

	}

	void erase(int index) {

		if (index < 0 || index >= _size) return;

		Node* pre = nullptr;
		Node* cur = _head;

		size_t i = 0;
		while (i < index) {

			pre = cur;
			cur = cur->next;

			i++;

		}

		if (pre == nullptr)
		{
			if (cur->next != nullptr)
			{
				_head = _head->next;
				_head->previous = nullptr;
			}
			else
			{
				_head = nullptr;
				_tail = nullptr;
			}
		}
		else
		{
			Node* temp = cur->next;
			pre->next = temp;
			if (temp != nullptr)
			{
				temp->previous = pre;

			}
			else
			{
				_tail = pre;
			}
		}

		_size--;
		delete cur;

	}

	void erase(Node* node) {

		if (node == nullptr) return;

		Node* pre = node->previous;
		Node* cur = node;
		Node* temp = node->next;

		if (pre != nullptr)
			pre->next = temp;
		if (temp != nullptr)
			temp->previous = pre;

		_size--;
		delete cur;

	}

	bool moveNode(int objectIndex, int targetIndex, bool toSwapPrevious = true)
	{
		int dif = targetIndex - objectIndex;

		if (objectIndex == targetIndex || _size < 2) return false;

		else if ((dif == 1 && toSwapPrevious) || (dif == -1 && !toSwapPrevious)) return false;


		Node* obj = findNode(objectIndex);
		Node* tar = findNode(targetIndex);

		if (obj == nullptr || tar == nullptr) return false;

		Node* objPre = obj->previous;
		Node* objNex = obj->next;
		Node* tarPre = tar->previous;
		Node* tarNex = tar->next;

		if (dif == 1 || dif == -1)
		{
			swapNode(obj, tar);
		}
		else if (!toSwapPrevious)
		{
			// obj = 2, tar = 5, objPre = (1), objNex = (3), tarPre = (4), tarNex = (6)
			// (1)<->2<->(3) | (4)<->5<->(6)
			// (1)->(3) | (1)<-2<->(3) | (4)<->5<->(6)
			if (objPre != nullptr)
				objPre->next = objNex;
			else
				_head = objNex;

			// (1)<->(3) | (1)<-2->(3) | (4)<->5<->(6)
			if (objNex != nullptr)
				objNex->previous = objPre;
			else
				_tail = objPre;

			// (1)<->(3) | 5<-2->(3) | (4)<->5<->(6)
			obj->previous = tar;
			// (1)<->(3) | 5<-2->(6) | (4)<->5<->(6)
			obj->next = tarNex;

			// (1)<->(3) | 5<-2<->(6) | (4)<->5->(6)
			if (tarNex != nullptr)
				tarNex->previous = obj;
			else
				_tail = obj;

			// (1)<->(3) | 5<->2<->(6) | (4)<->5<->2
			tar->next = obj;

		}
		else if (toSwapPrevious)
		{
			// obj = 2, tar = 5, objPre = (1), objNex = (3), tarPre = (4), tarNex = (6)
			// (1)<->2<->(3) | (4)<->5<->(6)
			// (1)->(3) | (1)<-2<->(3) | (4)<->5<->(6)
			if (objPre != nullptr)
				objPre->next = objNex;
			else
				_head = objNex;

			// (1)<->(3) | (1)<-2->(3) | (4)<->5<->(6)
			if (objNex != nullptr)
				objNex->previous = objPre;
			else
				_tail = objPre;

			// (1)<->(3) | (4)<-2->(3) | (4)<->5<->(6)
			obj->previous = tarPre;
			// (1)<->(3) | (4)<-2->5 | (4)<->5<->(6)
			obj->next = tar;

			// (1)<->(3) | (4)<->2->5 | (4)<-5<->(6)
			if (tarPre != nullptr)
				tarPre->next = obj;
			else
				_head = obj;

			// (1)<->(3) | (4)<->2<->5 | 2<->5<->(6)
			tar->previous = obj;

		}
		else {
			return false;
		}

		return true;

	}

	bool swapNode(Node* firstNode, Node* secondNode)
	{
		if (firstNode == secondNode || _size < 2 || firstNode == nullptr || secondNode == nullptr) return false;

		Node* firPre = firstNode->previous;
		Node* firNex = firstNode->next;

		Node* secPre = secondNode->previous;
		Node* secNex = secondNode->next;

		if (firPre == secondNode) {

			firstNode->previous = secPre;
			firstNode->next = secondNode;

			secondNode->previous = firstNode;
			secondNode->next = firNex;
			if (firNex != nullptr)
				firNex->previous = secondNode;

			if (secPre != nullptr)
				secPre->next = firstNode;

		}
		else if (firNex == secondNode) {

			firstNode->previous = secondNode;
			firstNode->next = secNex;

			secondNode->previous = firPre;
			secondNode->next = firstNode;
			if (firPre != nullptr)
				firPre->next = secondNode;

			if (secNex != nullptr)
				secNex->previous = firstNode;

		}
		else {

			Node* firPre = firstNode->previous;
			Node* firNex = firstNode->next;

			Node* secPre = secondNode->previous;
			Node* secNex = secondNode->next;

			firstNode->previous = secPre;
			firstNode->next = secNex;

			secondNode->previous = firPre;
			secondNode->next = firNex;

			if (firPre != nullptr)
				firPre->next = secondNode;
			if (firNex != nullptr)
				firNex->previous = secondNode;

			if (secPre != nullptr)
				secPre->next = firstNode;
			if (secNex != nullptr)
				secNex->previous = firstNode;

		}

		if (firstNode->previous == nullptr)
			_head = firstNode;
		if (firstNode->next == nullptr)
			_tail = firstNode;

		if (secondNode->previous == nullptr)
			_head = secondNode;
		if (secondNode->next == nullptr)
			_tail = secondNode;

		return true;

	}

	bool swapNode(int firstIndex, int secondIndex) {

		if (firstIndex == secondIndex || _size < 2) return false;

		if (firstIndex > secondIndex)
		{
			secondIndex += firstIndex;
			firstIndex = secondIndex - firstIndex;
			secondIndex -= firstIndex;
		}

		Node* fir = findNode(firstIndex);
		Node* sec = findNode(secondIndex);

		if (fir == nullptr || sec == nullptr) return false;

		if ((secondIndex - firstIndex) == 1) {

			Node* firPre = fir->previous;
			Node* secNex = sec->next;

			fir->previous = sec;
			fir->next = secNex;

			sec->previous = firPre;
			sec->next = fir;
			if (firPre != nullptr)
				firPre->next = sec;

			if (secNex != nullptr)
				secNex->previous = fir;

		}
		else {

			Node* firPre = fir->previous;
			Node* firNex = fir->next;

			Node* secPre = sec->previous;
			Node* secNex = sec->next;

			fir->previous = secPre;
			fir->next = secNex;

			sec->previous = firPre;
			sec->next = firNex;

			if (firPre != nullptr)
				firPre->next = sec;
			firNex->previous = sec;

			secPre->next = fir;
			if (secNex != nullptr)
				secNex->previous = fir;

		}

		if (fir->next == nullptr)
			_tail = fir;

		if (sec->previous == nullptr)
			_head = sec;

		return true;

	}

	Node* findNode(int index) {

		if (_size <= 0 || index < 0 || index >= _size) return nullptr;

		Node* temp = _head;

		for (size_t i = 0; i < index; i++)
		{
			temp = temp->next;
		}

		return temp;

	}
	Node* findNode(DataType data) {

		if (_size <= 0 || data == nullptr) return nullptr;

		Node* temp = _head;

		for (size_t i = 0; i < _size; i++)
		{
			if (data == temp->data)
			{
				return temp;
			}
		}

		return nullptr;

	}
	int findIndex(Node* node) {

		if (_size <= 0 || node == nullptr) return -1;

		Node* temp = _head;

		for (size_t i = 0; i < _size; i++)
		{
			if (node == temp)
			{
				return i;
			}
		}

		return -1;

	}
	int findIndex(DataType data) {

		if (_size <= 0 || data == nullptr) return -1;

		Node* temp = _head;

		for (size_t i = 0; i < _size; i++)
		{
			if (data == temp->data)
			{
				return i;
			}
		}

		return -1;

	}

	DataType findData(int index) {

		if (_size <= 0 || index < 0 || index >= _size) return DataType();

		Node* temp = _head;

		for (size_t i = 0; i < index; i++)
		{
			temp = temp->next;
		}

		return temp->data;

	}

	void clear()
	{
		this->~DoubleLinkList();
	}

	int size() { return _size; }
};
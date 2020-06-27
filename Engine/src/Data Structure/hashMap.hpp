#pragma once

template <int SIZE, typename dataType>
class HashMap {

private:

	struct HashEntry {

		int key;
		dataType value;

		HashEntry() {

			key = 0;
			value = NULL;

		}

		HashEntry(int key, dataType value) {

			this->key = key;
			this->value = value;

		}

		~HashEntry() { }

	} **table;

public:

	HashMap() {

		table = new HashEntry*[TABLE_SIZE];

		for (int i = 0; i<TABLE_SIZE; i++) {

			table[i] = nullptr;

		}

	}

	~HashMap() {

		//Error when deleting

		for (int i = 0; i<TABLE_SIZE; i++) {

			if (table[i]!=nullptr) {

				//delete table[i];
				//table[i] = nullptr;

			}

			//delete[] table;

		}

	}

	int hashKey(int key) { return key%TABLE_SIZE; }

	void insert(int key, dataType value) {

		int hash = hashKey(key);

		while (table[hash]!=nullptr&&table[hash]->key!=key) {

			hash = hashKey(hash+1);

		}

		if (table[hash]!=nullptr) {
			delete table[hash];
			table[hash] = nullptr;
		}

		table[hash] = new HashEntry(key, value);

	}

	dataType search(int key) {

		int hash = hashKey(key);

		while (table[hash]!=nullptr&&table[hash]->key!=key) {

			hash = hashKey(hash+1);

		}

		if (table[hash]==nullptr) { return -1; }

		return table[hash]->value;

	}

	void remove(int key) {

		int hash = hashKey(key);

		while (table[hash]!=nullptr) {

			if (table[hash]->key==key) { break; }

			hash = hashKey(hash+1);

		}

		if (table[hash]==nullptr) { return; }

		delete table[hash];
		table[hash] = nullptr;

	}

};
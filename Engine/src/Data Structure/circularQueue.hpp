#pragma once

#include <cstdlib>

template <int SIZE, typename dataType>
class circularQueue {

private:

	int newest;
	int oldest;
	int size;

	dataType container[SIZE];

public:

	circularQueue() {

		newest = 0;
		oldest = 0;

		for (int i = 0; i<SIZE; ++i) {

			container[i] = NULL;

		}

	}

	void pushNewest(const dataType &toStore) {

		if (size!=0) { newest = ++newest%SIZE; }

		container[newest] = toStore;

		oldest = newest==oldest&&size>1 ? ++oldest%SIZE : oldest;

		if (size!=SIZE) { ++size; }

	}

	void pushOldest(const dataType &toStore) { //optional

		container[size==0 ? oldest : oldest+1%SIZE] = toStore;

		if (newest==oldest&&size>0) { ++newest; }

		if (size<2) { ++size; }

	}

	void popNewest() { //optional

		container[newest] = NULL;

		if (newest!=oldest) { newest = newest-1<0 ? SIZE-1 : --newest; }

		if (size>0) { --size; }

	}

	void popOldest() { //optional

		container[oldest] = NULL;

		if (oldest!=newest) { oldest = oldest+1>=SIZE ? 0 : ++oldest; }

		if (size>0) { --size; }

	}

	int getSize() { return size; }

	dataType getValue(const int &location) { return container[(newest-location<0 ? SIZE+(newest-location) : newest-location)]; }

	dataType getNewest() { return container[newest]; }

	dataType getOldest() { return container[oldest]; }

};
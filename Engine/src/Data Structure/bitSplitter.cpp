#include "bitSplitter.h"

BitSplitter_uInt::BitSplitter_uInt() {

	for (int i = 0; i < 4; ++i) { bytes[i] = 0; }

}

void BitSplitter_uInt::store(unsigned int value) {

	for (int i = 0; i < 4; ++i) {

		bytes[i] |= value;

		value >>= UCHAR_SIZE;

	}

}

unsigned int& const BitSplitter_uInt::extract() {

	unsigned int actualData = 0;

	for (int i = 3; i >= 0; --i) {

		actualData <<= UCHAR_SIZE;

		actualData |= bytes[i];

	}

	return actualData;

}

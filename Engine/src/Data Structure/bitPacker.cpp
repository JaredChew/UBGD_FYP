#include "bitPacker.h"

BitPacker_uInt::BitPacker_uInt() {

	data = 0;
	bitCount = 0;

}

void BitPacker_uInt::setData(const unsigned int& data, const unsigned int& bitCount) {
	this->data = data;
	this->bitCount = bitCount;
}

unsigned int& const BitPacker_uInt::getData() {
	return data;
}

unsigned int& const BitPacker_uInt::getBitCount() {
	return bitCount;
}

void BitPacker_uInt::reset() {

	data = 0;

	bitCount = 0;

}

bool BitPacker_uInt::pack(const unsigned int& value, const unsigned int& bitCount) {

	data = (data << bitCount) | value;

	this->bitCount += bitCount;

	return bitCount > UINT_SIZE ? false : true;

}

unsigned int& const BitPacker_uInt::unpack(const unsigned int& bitCount) {

	unsigned int processedValue = (1 << bitCount) - 1 & data;

	data = data >> bitCount;

	return processedValue;

}

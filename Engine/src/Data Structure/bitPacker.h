#pragma once

#define UINT_SIZE sizeof(unsigned int) * 8

class BitPacker_uInt {

private:

	unsigned int data;
	unsigned int bitCount;

public:
	BitPacker_uInt();

	void setData(const unsigned int& data, const unsigned int& bitCount);

	unsigned int& const getData();
	unsigned int& const getBitCount();

	void reset();

	bool pack(const unsigned int& value, const unsigned int& bitCount);

	unsigned int& const unpack(const unsigned int& bitCount);

};
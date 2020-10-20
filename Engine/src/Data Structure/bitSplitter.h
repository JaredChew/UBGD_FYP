#pragma once

#define UCHAR_SIZE sizeof(unsigned char) * 8

class BitSplitter_uInt {

private:

    unsigned char bytes[4];

public:

    BitSplitter_uInt();

    void store(unsigned int value);

    unsigned int& const extract();

};
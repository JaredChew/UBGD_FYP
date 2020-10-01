#include "bitOperation.h"

#include <math.h>

int& const Utilities::BitOp::binaryToDenary(long long binary) {

	/* https://www.programiz.com/cpp-programming/examples/binary-decimal-convert */

	int decimalNumber = 0, i = 0, remainder;

	while (binary != 0) {

		remainder = binary % 10;

		binary /= 10;

		decimalNumber += (int)(remainder * pow(2, i));

		++i;

	}

	return decimalNumber;

}

int Utilities::BitOp::countUsedBits(const unsigned int& value) {

	return value == 0 ? 1 : log(value) / log(2) + 1;

}
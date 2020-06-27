#include "generalUtil.h"

template<typename custom> bool Utilities::compareGreather(custom comparingWith, custom toBeComparedWith) {

	return (comparingWith > toBeComparedWith);

}

template<typename custom> bool Utilities::compareLesser(custom comparingWith, custom toBeComparedWith) {

	return (comparingWith > toBeComparedWith);

}

double Utilities::removeHeadingZeros(double value) {

	while (value < 1.0) { value * 10.0; }

	return value;

}
#include "bitData.h"

BitData64::BitData64(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData64::reset(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData64::set(const int &location, const bool &flag) {

	if (location >= 64) { return; }

	if (flag) { data = data | (1 << location); }
	else { data = data & (~(1 << location)); }

}

bool BitData64::get(const int &location) {

	if (location >= 64) { return false; }

	return 1 & (data >> location);

}

BitData32::BitData32(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData32::reset(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData32::set(const int &location, const bool &flag) {

	if (location >= 32) { return; }

	if (flag) { data = data | (1 << location); }
	else { data = data & (~(1 << location)); }

}

bool BitData32::get(const int &location) {

	if (location >= 32) { return false; }

	return 1 & (data >> location);

}

BitData16::BitData16(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData16::reset(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData16::set(const int &location, const bool &flag) {

	if (location >= 16) { return; }

	if (flag) { data = data | (1 << location); }
	else { data = data & (~(1 << location)); }

}

bool BitData16::get(const int &location) {

	if (location >= 16) { return false; }

	return 1 & (data >> location);

}

BitData8::BitData8(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData8::reset(const bool &allTrue) {

	data = allTrue ? ~0 : 0;

}

void BitData8::set(const int &location, const bool &flag) {

	if (location >= 8) { return; }

	if (flag) { data = data | (1 << location); }
	else { data = data & (~(1 << location)); }

}

bool BitData8::get(const int &location) {

	if (location >= 8) { return false; }

	return 1 & (data >> location);

}
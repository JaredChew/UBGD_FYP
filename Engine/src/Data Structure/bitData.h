#pragma once

class BitData64 {

private:

	unsigned long long int data;

public:

	BitData64(const bool &allTrue = 0);

	void reset(const bool &allTrue = 0);

	void set(const int &location, const bool &flag);
	bool get(const int &location);

};



class BitData32 {

private:

	unsigned int data;

public:

	BitData32(const bool &allTrue = 0);

	void reset(const bool &allTrue = 0);

	void set(const int &location, const bool &flag);
	bool get(const int &location);

};



class BitData16 {

private:

	unsigned short int data;

public:

	BitData16(const bool &allTrue = 0);

	void reset(const bool &allTrue = 0);

	void set(const int &location, const bool &flag);
	bool get(const int &location);

};



class BitData8 {

private:

	unsigned char data;

public:

	BitData8(const bool &allTrue = 0);

	void reset(const bool &allTrue = 0);

	void set(const int &location, const bool &flag);
	bool get(const int &location);

};
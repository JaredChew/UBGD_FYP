#pragma once

#include <unordered_map>

class Resources;

class Library {

private:

	std::unordered_multimap<int, Resources*> database;

	int category;
	int selection;

public:
	Library();
	~Library();

	void archive(const int& category, const Resources* resource);
	void remove(const int& category, const int& selection);

	void browse(const int& category);
	void select(const int& selection);

	Resources* const view();

};
#pragma once

#include <list>
#include <string>

class Transform;

class Entity {

public:
	Entity* parent;
	std::list<Entity*> child;

	Transform *transform;

	unsigned int id;
	int group;
	std::string name;

public:
	Entity();
	virtual ~Entity();

	//void kill();

};
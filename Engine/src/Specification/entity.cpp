#include "entity.h"

#include "../Compound/transform.h"

Entity::Entity() {

	transform = new Transform();

}

Entity::~Entity() {

	delete transform;
	transform = nullptr;

}
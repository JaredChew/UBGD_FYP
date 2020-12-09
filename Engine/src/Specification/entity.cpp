#include "entity.h"

#include "../Compound/transform.h"


Entity::Entity() {

	transform = new Transform();
	child.clear();
}

Entity::~Entity() {

	child.clear();

	delete transform;
	transform = nullptr;

}
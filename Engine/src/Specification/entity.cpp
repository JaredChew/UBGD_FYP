#include "entity.h"

Entity::Entity(const bool &collision, const bool &physical) {

	boundary = collision ? new Boundary(&transform) : nullptr;
	physics = physical ? new Physics(&transform) : nullptr;

}

Entity::~Entity() {

	delete boundary;
	boundary = nullptr;

	delete physics;
	physics = nullptr;

}
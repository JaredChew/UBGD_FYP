#include "entity.h"

#include "../Compound/transform.h"
#include "../Modules BackEnd/boundary.h"
#include "../Modules BackEnd/physics.h"

Entity::Entity(const bool &collision, const bool &physical) {

	transform = new Transform();

	boundary = collision ? new Boundary(transform) : nullptr;
	physics = physical ? new Physics(transform) : nullptr;

}

Entity::~Entity() {

	delete boundary;
	boundary = nullptr;

	delete physics;
	physics = nullptr;

	delete transform;
	transform = nullptr;

}
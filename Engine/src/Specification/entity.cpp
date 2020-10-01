#include "entity.h"

#include "../Compound/transform.h"
#include "../Modules BackEnd/collision.h"
#include "../Modules BackEnd/physics.h"

Entity::Entity() { //const bool &boundary, const bool &physical

	transform = new Transform();

	//collision = boundary ? new Collision(transform) : nullptr;
	//physics = physical ? new Physics(transform) : nullptr;

}

Entity::~Entity() {

	//delete collision;
	//collision = nullptr;

	//delete physics;
	//physics = nullptr;

	delete transform;
	transform = nullptr;

}
#pragma once

#include "../Compound/transform.h"

#include "../Modules BackEnd/boundary.h"
#include "../Modules BackEnd/physics.h"

class Entity {

public:
	Transform transform;

	Boundary *boundary; //Collision* collision;
	Physics *physics;

public:
	Entity(const bool &collision = false, const bool &physical = false);
	virtual ~Entity();

};
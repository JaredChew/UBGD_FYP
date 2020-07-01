#pragma once

class Transform;
class Physics;
class Boundary;

class Entity {

public:
	Transform *transform;

	Boundary *boundary; //Collision* collision;
	Physics *physics;

public:
	Entity(const bool &collision = false, const bool &physical = false);
	virtual ~Entity();

};
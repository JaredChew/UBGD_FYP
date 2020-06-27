#include "physics.h"

Physics::Physics(Transform *const transform) : transform(transform) {

	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);

	freefall = 9.81f;
	airResistance = 1.0f;
	surfaceResistance = 1.0f;

	gravity = false;
	friction = false;

}

Physics::~Physics() { }

void Physics::push(const float &force) {
	velocity += force; //velocity -= (transform.getFacingDirection() * force);
}

void Physics::drag(const float &force) {

	if (glm::length(velocity) > 0.0f) {

		velocity -= force; //velocity -= transform.getFacingDirection() * force;

		if (glm::length(velocity) < 0.0f) { velocity = glm::vec3(0.0f); }

	}

}

void Physics::accelerate(const glm::vec3 &acceleration) {
	this->acceleration += acceleration;
}

void Physics::setVelocity(const glm::vec3 &velocity) {
	this->velocity = velocity;
}

void Physics::setAcceleration(const glm::vec3 &acceleration) {
	this->acceleration = acceleration;
}

void Physics::setGravity(const bool &gravity) {
	this->gravity = gravity;
}

glm::vec3 Physics::getVelocity() {
	return velocity;
}

glm::vec3 Physics::getAcceleration() {
	return acceleration;
}

bool Physics::getGravity() {
	return gravity;
}

void Physics::update() {

	velocity += acceleration;

	if (gravity) { velocity += glm::vec3(0.0f, freefall - airResistance, 0.0f); }

	if (friction) { velocity -= surfaceResistance; }

	transform->translate(velocity); //* Window::getDeltaTime_Seconds();

}

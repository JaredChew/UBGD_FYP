#include "physics.h"

#include "../Compound/transform.h"

Physics::Physics(Transform *const transform) : transform(transform) {

	velocity = glm::vec3(0.0f);
	momentum = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);
	resultantForce = glm::vec3(0.0f);

	mass = 1.0f;
	freefall = 9.81f;
	airResistance = 1.0f;
	surfaceResistance = 1.0f;

	weight = mass * freefall;

	gravity = false;
	friction = false;

	previousPosition = transform->getPosition();

}

Physics::~Physics() { }

void Physics::applyGravity(const float& deltaTime) {
	if (gravity) { acceleration += (glm::vec3(0.0f, freefall - airResistance, 0.0f) * weight) * deltaTime; }
}

void Physics::applyFriction(const float& deltaTime) {
	if (friction) { acceleration -= (surfaceResistance * weight) * deltaTime; }
}

void Physics::calculateVelocity(const float& deltaTime) {
	velocity = (transform->getPosition() - previousPosition) / deltaTime;
}

void Physics::calculateResultantForce(const float& deltaTime) {

	glm::vec3 oldMomentum = momentum;

	momentum = mass * velocity;

	resultantForce = (momentum - oldMomentum) / deltaTime;

}

void Physics::pushPull(const float &force, const glm::vec3 &acceleration) {
	this->acceleration += ((force) * acceleration);
}

void Physics::accelerate(const glm::vec3 &acceleration) {
	this->acceleration += mass * acceleration;
}

void Physics::enableGravity(const bool& gravity) {
	this->gravity = gravity;
}

void Physics::enableFriction(const bool& friction) {
	this->friction = friction;
}

bool Physics::isGravityEnabled() {
	return gravity;
}

bool Physics::isFrictionEnabled() {
	return friction;
}

void Physics::setMass(const float& mass) {

	this->mass = mass;

	weight = mass * freefall;

}

void Physics::setFreefall(const float& freefall) {
	this->freefall = freefall;
}

void Physics::setAirResistance(const float& airResistance) {
	this->airResistance = airResistance;
}

void Physics::setSurfaceResistance(const float& surfaceResistance) {
	this->surfaceResistance = surfaceResistance;
}

glm::vec3 Physics::getVelocity() {
	return velocity;
}

glm::vec3 Physics::getMomentum() {
	return momentum;
}

glm::vec3 Physics::getAcceleration() {
	return acceleration;
}

glm::vec3 Physics::getResultantForce() {
	return resultantForce;
}

void Physics::update(const float& deltaTime) {

	calculateVelocity(deltaTime);
	calculateResultantForce(deltaTime);

	applyGravity(deltaTime);
	applyFriction(deltaTime);

	transform->translate(acceleration);

	previousPosition = transform->getPosition();

}

#include "physics.h"

#include "collision.h"

#include "../Compound/transform.h"

Physics::Physics(Transform* const transform, Collision* const collision) : transform(transform), collision(collision){

	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);

	mass = 1.0f;
	freeFall = 9.81f;
	airResistance = 1.0f;
	surfaceResistance = 1.0f;

	gravity = false;
	friction = false;

}

Physics::~Physics() { }

void Physics::applyFriction(const float& deltaTime) {

	if (getSpeed() <= 0.0f) { return; }

	velocity -= glm::normalize(-velocity) * (surfaceResistance / mass) * deltaTime;
	velocity -= glm::normalize(-velocity) * (airResistance / mass) * deltaTime;

	if (glm::length(velocity) < 0.0f) { velocity = glm::vec3(0.0f); }

}

void Physics::applyGravity(const float& deltaTime) {
	velocity += glm::vec3(0.0f, freeFall, 0.0f) * deltaTime;
}

void Physics::pushPull(const glm::vec3& acceleration) {
	this->velocity += mass * acceleration;
}

void Physics::setAcceleration(const glm::vec3& acceleration) {
	this->acceleration = acceleration;
}

glm::vec3& const Physics::getAcceleration() {
	return acceleration;
}

void Physics::setVelocity(const glm::vec3& velocity) {
	this->velocity = velocity;
}

glm::vec3& const Physics::getVelocity() {
	return velocity;
}

void Physics::enableGravity(const bool& gravity) {
	this->gravity = gravity;
}

void Physics::enableFriction(const bool& friction) {
	this->friction = friction;
}
bool& const Physics::isGravityEnabled() {
	return gravity;
}

bool& const Physics::isFrictionEnabled() {
	return friction;
}

void Physics::setMass(const float& mass) {
	this->mass = mass;
}

void Physics::setFreeFall(const float& freeFall) {
	this->freeFall = freeFall;
}

void Physics::setAirResistance(const float& airResistance) {
	this->airResistance = airResistance;
}

void Physics::setSurfaceResistance(const float& surfaceResistance) {
	this->surfaceResistance = surfaceResistance;
}

float& const Physics::getMass() {
	return mass;
}

float& const Physics::getFreeFall() {
	return freeFall;
}

float& const Physics::getAirResistance() {
	return airResistance;
}

float& const Physics::getSurfaceResistance() {
	return surfaceResistance;
}

float Physics::getSpeed() {
	return glm::length(velocity);
}

float Physics::getMomentum() {
	return mass * getSpeed();
}

float Physics::getWeight() {
	return mass * freeFall;
}

void Physics::update(const float& deltaTime) {

	velocity += acceleration * deltaTime;

	if (gravity) { applyGravity(deltaTime); }

	if (friction) { applyFriction(deltaTime); }

	transform->translate(velocity);

}

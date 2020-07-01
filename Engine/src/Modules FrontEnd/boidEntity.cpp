#include "boidEntity.h"

#include "../Modules BackEnd/window.h"
#include "../Modules BackEnd/physics.h"

#include "../Compound/transform.h"

BoidEntity::BoidEntity() : Entity(false, true) {

	Utilities::Random::seedRandom();

	velLimit = 1.0f;
	accelLimit = 1.0f;

	attractorDistance = 1.0f;
	repellerDistance = 1.0f;
	boundaryRadius = 1.0f;

	repellerWeight = 1.0f;
	attractorWeight = 1.0f;

	initial = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);

	centerPosition = glm::vec3(0.0f);

	resultant = glm::vec3(Utilities::Random::randBetweenFloat(-10.0f, 10.0f), Utilities::Random::randBetweenFloat(-10.0f, 10.0f), 0.0f);

	physics->setVelocity(glm::vec3(Utilities::Random::randBetweenFloat(-10.0f, 10.0f), Utilities::Random::randBetweenFloat(-10.0f, 10.0f), 0.0f));

	transform->setPosition(glm::vec3(Utilities::Random::randBetweenFloat(-50.0f, 50.0f), Utilities::Random::randBetweenFloat(-50.0f, 50.0f), 0.0f));

}

BoidEntity::~BoidEntity() { }

glm::vec3 BoidEntity::calculateResultant(const glm::vec3 &initial, const glm::vec3 &acceleration) {
	return glm::length(initial + acceleration) < accelLimit ? initial + acceleration : glm::normalize(initial + acceleration) * accelLimit;
}

bool BoidEntity::withinDistance(const glm::vec3 object, const float &distance) {

	if (distance == 0.0f) { return true; }

	return abs(glm::length2(transform->getPosition() - object)) < distance * distance;

}

void BoidEntity::applyRepellent(const glm::vec3 &repeller) {

	if (!withinDistance(repeller, repellerDistance)) { return; }

	initial = glm::vec3(repeller.x - transform->getPosition().x, repeller.y - transform->getPosition().y, repeller.z - transform->getPosition().z);
	acceleration = glm::vec3(transform->getPosition().x - physics->getVelocity().x, physics->getVelocity().y - transform->getPosition().y, physics->getVelocity().z - transform->getPosition().z);

	resultant += calculateResultant(initial, acceleration) * -repellerWeight;

}

void BoidEntity::applyAttraction(const glm::vec3 &attractor) {

	if (!withinDistance(attractor, attractorDistance)) { return; }

	initial = glm::vec3(physics->getVelocity().x - transform->getPosition().x, physics->getVelocity().y - transform->getPosition().y, physics->getVelocity().z - transform->getPosition().z);
	acceleration = glm::vec3(attractor.x - physics->getVelocity().x, attractor.y - physics->getVelocity().y, attractor.z - physics->getVelocity().z);
	
	resultant += calculateResultant(initial, acceleration) * attractorWeight;

}

void BoidEntity::stayWithinBoundary() {

	if (withinDistance(centerPosition, boundaryRadius)) { return; }

	initial = glm::vec3(physics->getVelocity().x - transform->getPosition().x, physics->getVelocity().y - transform->getPosition().y, physics->getVelocity().z - transform->getPosition().z);
	acceleration = glm::vec3(centerPosition.x - physics->getVelocity().x, centerPosition.y - physics->getVelocity().y, centerPosition.z - physics->getVelocity().z);

	resultant += calculateResultant(initial, acceleration);

}

void BoidEntity::update() {

	for (int i = 0; i < attractor.size(); ++i) { applyAttraction(attractor[i]->getPosition()); }
	for (int i = 0; i < repeller.size(); ++i) { applyRepellent(repeller[i]->getPosition()); }

	stayWithinBoundary();

}

void BoidEntity::postUpdate() {

	if (glm::length(resultant) > velLimit) { resultant = glm::normalize(resultant) * velLimit; }

	float rotate = atan2(resultant.y, resultant.x) * (float)(180.0f / glm::pi<float>());

	transform->setRotationLocal(glm::vec3(0.0f, 0.0f, -rotate));

	physics->setVelocity(resultant * (float)Window::getDeltaTime_Seconds());
	physics->update();

}

void BoidEntity::addAttractor(Transform *const attractor) {
	this->attractor.push_back(attractor);
}

void BoidEntity::addRepeller(Transform *const repeller) {
	this->repeller.push_back(repeller);
}

void BoidEntity::removeAttractor(Transform *const attractor) {

	for (int i = 0; i < this->attractor.size(); ++i) {

		if (this->attractor[i] == attractor) {

			this->attractor.erase(this->attractor.begin() + i);

		}

	}

}

void BoidEntity::removeRepeller(Transform *const repeller) {

	for (int i = 0; i < this->repeller.size(); ++i) {

		if (this->repeller[i] == repeller) {

			this->repeller.erase(this->repeller.begin() + i);

		}

	}

}

void BoidEntity::setVelocityLimit(const float &velLimit) {
	this->velLimit = velLimit;
}

void BoidEntity::setAccelerationLimit(const float &accelLimit) {
	this->accelLimit = accelLimit;
}

void BoidEntity::setAttractorDistance(const float &attractorDistance) {
	this->attractorDistance = attractorDistance;
}

void BoidEntity::setRepellerDistance(const float &repellerDistance) {
	this->repellerDistance = repellerDistance;
}

void BoidEntity::setBoundaryRadius(const float &boundaryRadius) {
	this->boundaryRadius = boundaryRadius;
}

void BoidEntity::setAttractorWeight(const float &attractorWeight) {
	this->attractorWeight = attractorWeight;
}

void BoidEntity::setRepellerWeight(const float &repellerWeight) {
	this->repellerWeight = repellerWeight;
}

void BoidEntity::setCenterPosition(const glm::vec3 &centerPosition) {
	this->centerPosition = centerPosition;
}

void BoidEntity::effectVelocity(const glm::vec3 &acceleration) {
	resultant += glm::length(acceleration) < accelLimit ? acceleration : glm::normalize(acceleration) * accelLimit;
}

float BoidEntity::getVelLimit() {
	return velLimit;
}

float BoidEntity::getAccelLimit() {
	return accelLimit;
}

float BoidEntity::getAttractorDistance() {
	return attractorDistance;
}

float BoidEntity::getRepellerDistance() {
	return repellerDistance;
}

float BoidEntity::getBoundaryRadius() {
	return boundaryRadius;
}

float BoidEntity::getAttractorWeight() {
	return attractorWeight;
}

float BoidEntity::getRepellerWeight() {
	return repellerWeight;
}

glm::vec3 BoidEntity::getCenterPosition() {
	return centerPosition;
}

glm::vec3 BoidEntity::getResultant() {
	return resultant;
}

glm::vec3 BoidEntity::getPosition() {
	return transform->getPosition();
}

glm::vec3 BoidEntity::getVelocity() {
	return physics->getVelocity();
}
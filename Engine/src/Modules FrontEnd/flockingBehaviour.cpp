#include "flockingBehaviour.h"

#include "boidEntity.h"

FlockingBehaviour::FlockingBehaviour(const int& maxmimumBoids) {

	currentTotalBoids = 0;
	neighbourCount = 0;

	seperationResultant = glm::vec3(0.0f);
	alignmentResultant = glm::vec3(0.0f);
	cohesionResultant = glm::vec3(0.0f);

	seperationWeight = 1.0f;
	alignmentWeight = 1.0f;
	cohesionWeight = 1.0f;

	seperationDistance = 1.0f;
	alignmentDistance = 1.0f;
	cohesionDistance = 1.0f;

	this->maxmimumBoids = maxmimumBoids;

	boid = new BoidEntity * [maxmimumBoids];

}

FlockingBehaviour::~FlockingBehaviour() {

	for (int i = 0; i < maxmimumBoids; ++i) { boid[i] = nullptr; }

	delete[] boid;
	boid = nullptr;

}

void FlockingBehaviour::calculateCohesion(const glm::vec3& current) {

	cohesionResultant /= neighbourCount;

	cohesionResultant = cohesionResultant - current;

	cohesionResultant *= cohesionWeight;

}

void FlockingBehaviour::calculateAlignment() {

	alignmentResultant /= neighbourCount;

	alignmentResultant *= alignmentWeight;

}

void FlockingBehaviour::calculateSeperation() {

	seperationResultant /= neighbourCount;

	seperationResultant *= -1;

	seperationResultant *= seperationWeight;

}

float FlockingBehaviour::calculateDistance(const glm::vec3& current, const glm::vec3& against) {
	return abs(glm::length2(current - against));
}

void FlockingBehaviour::processCohesion(BoidEntity* const current) {

	neighbourCount = 0;

	cohesionResultant = glm::vec3(0.0f);

	for (int i = 0; i < currentTotalBoids; ++i) {

		if (current == boid[i]) { continue; }

		float distance = calculateDistance(current->getPosition(), boid[i]->getPosition());

		if (distance > cohesionDistance * cohesionDistance) { continue; }

		++neighbourCount;

		cohesionResultant += boid[i]->getPosition();

	}

	if (neighbourCount <= 0) { return; }

	calculateCohesion(current->getPosition());

}

void FlockingBehaviour::processAlignment(BoidEntity* const current) {

	neighbourCount = 0;

	alignmentResultant = glm::vec3(0.0f);

	for (int i = 0; i < currentTotalBoids; ++i) {

		if (current == boid[i]) { continue; }

		float distance = calculateDistance(current->getPosition(), boid[i]->getPosition());

		if (distance > alignmentDistance * alignmentDistance) { continue; }

		++neighbourCount;

		alignmentResultant += boid[i]->getVelocity();

	}

	if (neighbourCount <= 0) { return; }

	calculateAlignment();

}

void FlockingBehaviour::processSeperation(BoidEntity* const current) {

	neighbourCount = 0;

	seperationResultant = glm::vec3(0.0f);

	for (int i = 0; i < currentTotalBoids; ++i) {

		if (current == boid[i]) { continue; }

		float distance = calculateDistance(current->getPosition(), boid[i]->getPosition());

		if (distance > seperationDistance * seperationDistance) { continue; }

		++neighbourCount;

		seperationResultant += boid[i]->getPosition() - current->getPosition();

	}

	if (neighbourCount <= 0) { return; }

	calculateSeperation();

}

void FlockingBehaviour::update(const float& deltaTimeSeconds) {

	for (int i = 0; i < currentTotalBoids; ++i) { boid[i]->update(); }

	for (int i = 0; i < currentTotalBoids; ++i) {

		processCohesion(boid[i]);
		processAlignment(boid[i]);
		processSeperation(boid[i]);

		boid[i]->effectVelocity(cohesionResultant + alignmentResultant + seperationResultant);

	}

	for (int i = 0; i < currentTotalBoids; ++i) { boid[i]->postUpdate(deltaTimeSeconds); }

}

bool FlockingBehaviour::addBoid(BoidEntity* const boid) {

	if (currentTotalBoids >= maxmimumBoids) { return false; }

	this->boid[currentTotalBoids] = boid;

	++currentTotalBoids;

	return true;

}

bool FlockingBehaviour::removeBoid(const int& amount) {

	if (currentTotalBoids <= 0) { return false; }

	for (int i = 0; i < amount; ++i) {

		boid[currentTotalBoids] = nullptr;

		--currentTotalBoids;

	}

	return true;

}

void FlockingBehaviour::setSeperationDistance(const float& seperationDistance) {
	this->seperationDistance = seperationDistance;
}

void FlockingBehaviour::setAlignmentDistance(const float& alignmentDistance) {
	this->alignmentDistance = alignmentDistance;
}

void FlockingBehaviour::setCohesionDistance(const float& cohesionDistance) {
	this->cohesionDistance = cohesionDistance;
}

void FlockingBehaviour::setSeperationWeight(const float& seperationWeight) {
	this->seperationWeight = seperationWeight;
}

void FlockingBehaviour::setAlignmentWeight(const float& alignmentWeight) {
	this->alignmentWeight = alignmentWeight;
}

void FlockingBehaviour::setCohesionWeight(const float& cohesionWeight) {
	this->cohesionWeight = cohesionWeight;
}

float FlockingBehaviour::getSeperationDistance() {
	return seperationDistance;
}

float FlockingBehaviour::getAlignmentDistance() {
	return alignmentDistance;
}

float FlockingBehaviour::getCohesionDistance() {
	return cohesionDistance;
}

float FlockingBehaviour::getSeperationWeight() {
	return seperationWeight;
}

float FlockingBehaviour::getAlignmentWeight() {
	return alignmentWeight;
}

float FlockingBehaviour::getCohesionWeight() {
	return cohesionWeight;
}

int FlockingBehaviour::getMaximumBoids() {
	return maxmimumBoids;
}

int FlockingBehaviour::getCurrentTotalBoids() {
	return currentTotalBoids;
}

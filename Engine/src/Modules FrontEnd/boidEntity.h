#pragma once

#include <vector>

#include <glm/gtx/norm.hpp>

#include "../Specification/entity.h"

#include "../Utilities/random.h"

class BoidEntity : protected Entity {

private:

	std::vector<Transform*> attractor;
	std::vector<Transform*> repeller;

	glm::vec3 initial;
	glm::vec3 acceleration;
	glm::vec3 resultant;

	glm::vec3 centerPosition;

	float velLimit;
	float accelLimit;

	float attractorDistance;
	float repellerDistance;
	float boundaryRadius;

	float attractorWeight;
	float repellerWeight;

	bool isActive;

private:

	bool withinDistance(const glm::vec3 object, const float &distance);

	void applyAttraction(const glm::vec3 &attractor);
	void applyRepellent(const glm::vec3 &repeller);

	void stayWithinBoundary();

	glm::vec3 calculateResultant(const glm::vec3 &initial, const glm::vec3 &acceleration);

public:

	BoidEntity();
	~BoidEntity();

	void update();
	void postUpdate(const float& deltaTime_Seconds);

	void addAttractor(Transform *const attractor);
	void addRepeller(Transform *const repeller);

	void removeAttractor(Transform *const attractor);
	void removeRepeller(Transform *const repeller);

	void setVelocityLimit(const float &velLimit);
	void setAccelerationLimit(const float &accelLimit);

	void setAttractorDistance(const float &attractorDistance);
	void setRepellerDistance(const float &repellerDistance);
	void setBoundaryRadius(const float &boundaryRadius);

	void setAttractorWeight(const float &attractorWeight);
	void setRepellerWeight(const float &repellerWeight);

	void setCenterPosition(const glm::vec3 &centerPosition);

	void effectVelocity(const glm::vec3 &velocity);

	float getVelLimit();
	float getAccelLimit();

	float getAttractorDistance();
	float getRepellerDistance();
	float getBoundaryRadius();

	float getAttractorWeight();
	float getRepellerWeight();

	glm::vec3 getCenterPosition();

	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::vec3 getResultant();

};

/*

	initial = glm::vec3(transform.getPosition().x - physics->getVelocity().x, transform.getPosition().y - physics->getVelocity().y, transform.getPosition().z - physics->getVelocity().z);
	acceleration = glm::vec3(physics->getVelocity().x - attractor->getPosition().x, physics->getVelocity().y - attractor->getPosition().y, physics->getVelocity().z - attractor->getPosition().z);

	initial = glm::vec3(physics->getVelocity().x - transform.getPosition().x, transform.getPosition().y - physics->getVelocity().y, transform.getPosition().z - physics->getVelocity().z);
	acceleration = glm::vec3(repeller.x - physics->getVelocity().x, repeller.y - physics->getVelocity().y, repeller.z - physics->getVelocity().z);

*/
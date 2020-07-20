#pragma once

#include <glm/vec3.hpp>

class Transform;

class Physics {

private:

	Transform *const transform;

private:

	glm::vec3 velocity;
	glm::vec3 momentum;
	glm::vec3 acceleration;
	glm::vec3 resultantForce;

	glm::vec3 previousPosition;

	float mass;
	float weight;
	float freefall;
	float airResistance;
	float surfaceResistance;

	bool gravity;
	bool friction;

private:

	void applyGravity(const float& deltaTime);
	void applyFriction(const float& deltaTime);

	void calculateVelocity(const float& deltaTime);
	void calculateResultantForce(const float& deltaTime);

public:

	Physics(Transform *const transform);
	~Physics();

	void pushPull(const float &force, const glm::vec3& acceleration);
	void accelerate(const glm::vec3 &acceleration);

	void enableGravity(const bool& gravity);
	void enableFriction(const bool& friction);

	bool isGravityEnabled();
	bool isFrictionEnabled();

	glm::vec3 getVelocity();
	glm::vec3 getMomentum();
	glm::vec3 getAcceleration();
	glm::vec3 getResultantForce();

	void setMass(const float& mass);
	void setFreefall(const float& freefall);
	void setAirResistance(const float& airResistance);
	void setSurfaceResistance(const float& surfaceResistance);

	void update(const float& deltaTime);

};
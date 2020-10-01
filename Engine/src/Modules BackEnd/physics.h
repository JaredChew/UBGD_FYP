#pragma once

#include <glm/vec3.hpp>
#include <glm/common.hpp>

class Transform;
class Collision;

class Physics {

private:

	Transform* const transform;
	Collision* const collision;

private:

	glm::vec3 velocity;
	glm::vec3 acceleration;

	float mass;
	float freeFall;
	float airResistance;
	float surfaceResistance;

	bool gravity;
	bool friction;

private:

	void applyGravity(const float& deltaTime);
	void applyFriction(const float& deltaTime);

public:

	Physics(Transform* const transform, Collision* const collision);
	~Physics();

	void pushPull(const glm::vec3& acceleration);

	void setVelocity(const glm::vec3& velocity);
	void setAcceleration(const glm::vec3& acceleration);

	glm::vec3& const getVelocity();
	glm::vec3& const getAcceleration();

	void enableGravity(const bool& gravity);
	void enableFriction(const bool& friction);

	bool& const isGravityEnabled();
	bool& const isFrictionEnabled();

	void setMass(const float& mass);
	void setFreeFall(const float& freeFall);
	void setAirResistance(const float& airResistance);
	void setSurfaceResistance(const float& surfaceResistance);

	float& const getMass();
	float& const getFreeFall();
	float& const getAirResistance();
	float& const getSurfaceResistance();

	float getSpeed();
	float getWeight();
	float getMomentum();

	void update(const float& deltaTime);

};
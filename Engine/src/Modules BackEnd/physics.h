#pragma once

#include <glm/vec3.hpp>
#include <glm/common.hpp>

#include "../Compound/transform.h"

class Physics {

private:

	Transform *const transform;

private:

	glm::vec3 velocity;
	glm::vec3 acceleration;

	float freefall;
	float airResistance;
	float surfaceResistance;

	bool gravity;
	bool friction;

public:

	Physics(Transform *const transform);
	~Physics();

	void push(const float &force);
	void drag(const float &force);
	void accelerate(const glm::vec3 &acceleration);

	void setVelocity(const glm::vec3 &velocity);
	void setAcceleration(const glm::vec3 &acceleration);

	void setGravity(const bool &gravity);

	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();

	bool getGravity();

	void update();

};
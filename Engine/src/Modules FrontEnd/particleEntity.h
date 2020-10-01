#pragma once

#include <glm/vec3.hpp>

#include "../Specification/entity.h"

class Entity;
class Sprite;

class ParticleEntity : public Entity {

public:

	Sprite *const sprite;

private:

	float age;
	float lifespan;

	glm::vec3 velocity;
	glm::vec3 acceleration;

public:

	ParticleEntity(Sprite *const sprite, const float &lifespan);
	~ParticleEntity();

	void revive(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &acceleration);

	void update(const float& deltaTime_Seconds);
	void render();

	float& const getLifespan();
	float& const getAge();

	bool isDead();

};
#pragma once

#include "../Specification/entity.h"
#include "sprite.h"

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

	void update();
	void render();

	float getLifespan();
	float getAge();

	bool isDead();

};
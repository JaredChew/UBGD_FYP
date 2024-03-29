#include "particleEntity.h"

#include "sprite.h"

#include "particleEntity.h"

#include "../Modules BackEnd/window.h"

#include "../Compound/transform.h"

ParticleEntity::ParticleEntity(Sprite *const sprite, const float &lifespan) : sprite (sprite) {

	age = 0.0f;

	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);

	this->lifespan = lifespan;

	this->sprite->setIsBillboard(true);

}

ParticleEntity::~ParticleEntity() { }

void ParticleEntity::revive(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &acceleration) {

	transform->setPosition(position);

	this->velocity = velocity;
	this->acceleration = acceleration;

	age = lifespan;

}

void ParticleEntity::update(const float& deltaTime_Seconds) {

	if (isDead()) { return; }

	velocity += acceleration;

	transform->translate(velocity * deltaTime_Seconds);

	if (age > 0.0f) { age -= deltaTime_Seconds; }
	
}

void ParticleEntity::render() {

	if (isDead()) { return; }

	//if (sprite->getIsAnimatedSprite()) { sprite->renderAnimation(*transform); }
	//else { sprite->renderSprite(*transform); }

}

float& const ParticleEntity::getLifespan() {
	return lifespan;
}

float& const ParticleEntity::getAge() {
	return age;
}

bool ParticleEntity::isDead() {
	return age <= 0.0f;
}

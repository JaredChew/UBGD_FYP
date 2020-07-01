#include "particleSystem.h"

#include "sprite.h"
#include "particleEntity.h"
#include "particleAffector.h"

#include "../Compound/transform.h"

#include "../Utilities/random.h"

#include "../Modules BackEnd/window.h"

ParticleSystem::ParticleSystem(ParticleEntity *const particle, const int &maxParticlesEmittable, const float &emittionDelay, const bool &isEmittionEnable) {

	Utilities::Random::seedRandom();

	emittionCooldown = 0.0;

	this->particle = particle;
	this->maxParticlesEmittable = maxParticlesEmittable;
	this->emittionDelay = emittionDelay;
	this->isEmittionEnable = isEmittionEnable;

	transform = new Transform();

	//particleAffector = new DefaultParticleEffect();

	particlesEmitted = new ParticleEntity * [maxParticlesEmittable];

	for (int i = 0; i < maxParticlesEmittable; ++i) {

		particlesEmitted[i] = new ParticleEntity(*this->particle);

	}

}

ParticleSystem::~ParticleSystem() {

	for (int i = 0; i != maxParticlesEmittable; ++i) {

		delete particlesEmitted[i];
		particlesEmitted[i] = nullptr;

	}

	delete[] particlesEmitted;
	particlesEmitted = nullptr;

	delete particleAffector;
	particleAffector = nullptr;

	delete particle;
	particle = nullptr;

	delete transform;
	transform = nullptr;

}

void ParticleSystem::setEmittionDelay(const float &emittionDelay) {
	this->emittionDelay = emittionDelay;
}

void ParticleSystem::setIsEmittionEnable(const bool &isEmittionEnable) {
	this->isEmittionEnable = isEmittionEnable;
}

void ParticleSystem::setMaxParticlesEmittable(const int &maxParticlesEmittable) {
	this->maxParticlesEmittable = maxParticlesEmittable;
}

void ParticleSystem::setParticleAffector(ParticleAffector *const particleAffector) {

	delete this->particleAffector;
	this->particleAffector = nullptr;

	this->particleAffector = particleAffector;

}

void ParticleSystem::update(const float& deltaTime_Seconds) {

	for (int i = 0; i < maxParticlesEmittable; ++i) {

		if(particlesEmitted[i]->isDead() && emittionCooldown <= 0.0) {

			particlesEmitted[i]->revive(
				transform->getPosition() + particleAffector->getSpawnAffector(),
				particleAffector->getSpeedAffector() *particleAffector->getDirectionAffector(),
				particleAffector->getAccelerationAffector() *particleAffector->getDirectionAffector()
			);

			emittionCooldown = emittionDelay;
		
		}

		particlesEmitted[i]->sprite->setBlendColour(particleAffector->getColourAffector());
		particlesEmitted[i]->transform->rotateLocal(particleAffector->getRotateAffector());
		particlesEmitted[i]->transform->scaleLocal(glm::vec3(particleAffector->getSizeAffector().x, particleAffector->getSizeAffector().y, 0.0f));

		particlesEmitted[i]->update(deltaTime_Seconds);

	}

	particleAffector->update();

	if (emittionCooldown > 0.0) { emittionCooldown -= deltaTime_Seconds; }

}

void ParticleSystem::render() {

	for (int i = 0; i < maxParticlesEmittable; ++i) { particlesEmitted[i]->render(); }

}

ParticleEntity ParticleSystem::getEmittedParticle(const int &index) {
	return *particlesEmitted[index];
}

int ParticleSystem::numberOfParticlesAlive() {

	int counter = 0;

	for (int i = 0; i < maxParticlesEmittable; ++i) {

		if (!particlesEmitted[i]->isDead()) { ++counter; }

	}

	return counter;

}

int ParticleSystem::getMaxParticlesEmittable() {
	return maxParticlesEmittable;
}

float ParticleSystem::getEmittionDelay() {
	return emittionDelay;
}

bool ParticleSystem::getIsEmittionEnable() {
	return isEmittionEnable;
}
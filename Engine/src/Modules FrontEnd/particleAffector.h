#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class ParticleAffector {

protected:

	glm::vec4 colourAffector;

	glm::vec3 rotateAffector;
	glm::vec2 sizeAffector;

	glm::vec3 speedAffector;
	glm::vec3 directionAffector;
	glm::vec3 accelerationAffector;

	glm::vec3 spawnAffector;

public:

	virtual ~ParticleAffector() { }

	virtual void update() = 0;

	virtual glm::vec4 getColourAffector() = 0;

	virtual glm::vec3 getRotateAffector() = 0;
	virtual glm::vec2 getSizeAffector() = 0;

	virtual glm::vec3 getSpeedAffector() = 0;
	virtual glm::vec3 getDirectionAffector() = 0;
	virtual glm::vec3 getAccelerationAffector() = 0;

	virtual glm::vec3 getSpawnAffector() = 0;

};
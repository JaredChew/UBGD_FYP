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

	virtual glm::vec4& const getColourAffector() = 0;

	virtual glm::vec3& const getRotateAffector() = 0;
	virtual glm::vec2& const getSizeAffector() = 0;

	virtual glm::vec3& const getSpeedAffector() = 0;
	virtual glm::vec3& const getDirectionAffector() = 0;
	virtual glm::vec3& const getAccelerationAffector() = 0;

	virtual glm::vec3& const getSpawnAffector() = 0;

};
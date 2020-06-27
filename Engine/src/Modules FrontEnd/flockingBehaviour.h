#pragma once

#include <glm/gtx/norm.hpp>

#include "boidEntity.h"

class FlockingBehaviour {

private:

	BoidEntity **boid;

	int maxmimumBoids;
	int currentTotalBoids;
	int neighbourCount;

	float seperationDistance;
	float alignmentDistance;
	float cohesionDistance;

	float seperationWeight;
	float alignmentWeight;
	float cohesionWeight;

	glm::vec3 seperationResultant;
	glm::vec3 alignmentResultant;
	glm::vec3 cohesionResultant;

private:

	float calculateDistance(const glm::vec3 &current, const glm::vec3 &against);

	void calculateSeperation();
	void calculateAlignment();
	void calculateCohesion(const glm::vec3 &current);

	void processSeperation(BoidEntity *const current);
	void processAlignment(BoidEntity *const current);
	void processCohesion(BoidEntity *const current);

public:

	FlockingBehaviour(const int &maxmimumBoids);
	~FlockingBehaviour();

	void update();

	bool addBoid(BoidEntity *const boid);
	bool removeBoid(const int &amount);

	void setSeperationDistance(const float &seperationDistance);
	void setAlignmentDistance(const float &alignmentDistance);
	void setCohesionDistance(const float &cohesionDistance);

	void setSeperationWeight(const float &seperationWeight);
	void setAlignmentWeight(const float &alignmentWeight);
	void setCohesionWeight(const float &cohesionWeight);

	float getSeperationDistance();
	float getAlignmentDistance();
	float getCohesionDistance();

	float getSeperationWeight();
	float getAlignmentWeight();
	float getCohesionWeight();

	int getMaximumBoids();
	int getCurrentTotalBoids();

};
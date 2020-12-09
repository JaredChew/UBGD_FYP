#pragma once

#include <vector>

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#define MAX_DIRECTION_LIGHTS 8
#define MAX_POINT_LIGHTS 64
#define MAX_SPOT_LIGHTS 32

struct DirectionLight
{
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
struct PointLight
{
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
struct SpotLight
{
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class LightingContainer
{
private:

	std::vector<DirectionLight*> directionLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

	bool destroyAllLigthWhenDestructorCall;

public:
	LightingContainer(const bool& destroyAllLigthWhenDestructorCall = false)
	{
		directionLights.clear();
		pointLights.clear();
		spotLights.clear();

		this->destroyAllLigthWhenDestructorCall = destroyAllLigthWhenDestructorCall;

	}
	~LightingContainer()
	{
		if (!destroyAllLigthWhenDestructorCall) return;

		for (size_t i = 0; i < directionLights.size(); i++)
		{
			delete directionLights[i];
		}
		directionLights.clear();

		for (size_t i = 0; i < pointLights.size(); i++)
		{
			delete pointLights[i];
		}
		pointLights.clear();

		for (size_t i = 0; i < spotLights.size(); i++)
		{
			delete spotLights[i];
		}
		spotLights.clear();


	}

	bool setDirectionLight(const int& size, DirectionLight* directionLights)
	{
		if (size >= MAX_DIRECTION_LIGHTS) return false;

		this->directionLights.clear();
		for (size_t i = 0; i < size; i++)
		{
			this->directionLights.push_back(&directionLights[i]);
		}

		return true;
	}
	bool setPointLight(const int& size, PointLight* pointLights)
	{
		if (size >= MAX_POINT_LIGHTS) return false;

		this->pointLights.clear();
		for (size_t i = 0; i < size; i++)
		{
			this->pointLights.push_back(&pointLights[i]);
		}

		return true;
	}
	bool setSpotLight(const int& size, SpotLight* spotLights)
	{
		if (size >= MAX_SPOT_LIGHTS) return false;

		this->spotLights.clear();
		for (size_t i = 0; i < size; i++)
		{
			this->spotLights.push_back(&spotLights[i]);
		}

		return true;
	}

	bool addDirectionLight(DirectionLight* directionLight)
	{
		if (directionLights.size() >= MAX_DIRECTION_LIGHTS) return false;

		directionLights.push_back(directionLight);

		return true;
	}
	bool addPointLight(PointLight* pointLight)
	{
		if (pointLights.size() >= MAX_POINT_LIGHTS) return false;

		pointLights.push_back(pointLight);

		return true;
	}
	bool addSpotLight(SpotLight* spotLight)
	{
		if (spotLights.size() >= MAX_SPOT_LIGHTS) return false;

		spotLights.push_back(spotLight);

		return true;
	}


	std::vector<DirectionLight*>& getDirectionLights()
	{
		return directionLights;
	}
	std::vector<PointLight*>& getPointLights()
	{
		return pointLights;
	}
	std::vector<SpotLight*>& getSpotLights()
	{
		return spotLights;
	}

};

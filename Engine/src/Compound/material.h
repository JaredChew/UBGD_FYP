#pragma once

#include "texture.h"
#include <vector>
#include <glm/vec3.hpp>

class Texture;


class Material
{

public:
	
	enum class PhongTextureType : int { DIFFUSE = 0, SPECULAR, EMISSION };

public:

	Texture* textures[3];
	glm::vec3 color;
	float shininess;

	bool isDestroyTexturesWithMaterial;

public:

	Material(Texture* diffuse, Texture* specular, Texture* emission = nullptr, float shininess = 32.0f, const bool& isDestroyTexturesWithMaterial = false, const glm::vec3& color = glm::vec3(1.0f));
	Material(Texture* diffuse, float shininess = 32.0f, const bool& isDestroyTexturesWithMaterial = false, const glm::vec3& color = glm::vec3(1.0f));
	~Material();

	void setTexture(PhongTextureType type, Texture* texture);

};
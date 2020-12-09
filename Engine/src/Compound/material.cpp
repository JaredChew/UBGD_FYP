#include "material.h"

static Texture* textureNone = nullptr;

Material::Material(Texture* diffuse, Texture* specular, Texture* emission, float shininess, const bool& isDestroyTexturesWithMaterial, const glm::vec3& color)
{
	if (textureNone == nullptr)
		textureNone = new Texture("../Media/None.png");

	this->isDestroyTexturesWithMaterial = isDestroyTexturesWithMaterial;

	this->textures[0] = (diffuse == nullptr) ? textureNone : diffuse;
	this->textures[1] = (specular == nullptr) ? textureNone : specular;
	this->textures[2] = (emission == nullptr) ? textureNone : emission;

	this->color = color;

	this->shininess = shininess;
}
Material::Material(Texture* diffuse, float shininess, const bool& isDestroyTexturesWithMaterial, const glm::vec3& color)
{
	if (textureNone == nullptr)
		textureNone = new Texture("../Media/None.png");

	this->isDestroyTexturesWithMaterial = isDestroyTexturesWithMaterial;

	textures[0] = (diffuse == nullptr) ? textureNone : diffuse;
	textures[1] = textureNone;
	textures[2] = textureNone;

	this->color = color;

	this->shininess = shininess;
}
Material::~Material()
{
	if (!isDestroyTexturesWithMaterial) return;

	for (size_t i = 0; i < 3; i++)
	{
		if (textures[0] == textureNone) continue;
		
		delete textures[i];

	}

}

void Material::setTexture(PhongTextureType type, Texture* texture)
{
	if (texture == nullptr) return;

	textures[static_cast<int>(type)] = texture;
}
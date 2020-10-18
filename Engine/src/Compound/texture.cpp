#include "Texture.h"

#include <SOIL2/SOIL2.h>

#include "../Utilities/logger.h"
#include "../Manipulators/system.h"

// |*   Constructors   *|
Texture::Texture(const GLchar* dir) {

	System::initTexture(dir, textureID, width, height);

}

Texture::Texture( const int& width, const int& height) {

	this->width = width;
	this->height = height;

	System::initTexture(textureID, 1, this->width, this->height);

}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}


// |*   Getters   *|
const int& const Texture::getWidth(void)
{
	return width;

}

const int& const Texture::getHeight(void)
{
	return height;

}

GLuint& const Texture::getTextureID(void)
{
	return textureID;

}
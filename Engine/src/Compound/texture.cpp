#include "Texture.h"

#include <SOIL2/SOIL2.h>

#include "../Utilities/logger.h"
#include "../Manipulators/system.h"

// |*   Constructors   *|
Texture::Texture(const GLchar* dir) {

	this->path = std::string(dir);

	System::initTexture(this->path.c_str(), this->textureID, this->width, this->height, this->internalFormat, this->format);

}

Texture::Texture(const int& width, const int& height) {

	this->path = "";
	
	this->width = width;
	this->height = height;

	System::initTexture(this->textureID, 1, this->width, this->height, this->internalFormat, this->format);

}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

Texture::operator bool() const
{
	return (textureID != 0);
}


std::string& const Texture::getPath()
{
	return path;
}

// |*   Getters   *|
int& Texture::getWidth(void)
{
	return width;

}

int& Texture::getHeight(void)
{
	return height;

}

GLint& Texture::getInternalFormat()
{
	return internalFormat;
}

GLenum& Texture::getFormat()
{
	return format;
}

void Texture::setSize(const GLsizei& width, const GLsizei& height)
{
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Get texture size
	this->width = width;
	this->height = height;

	glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, NULL);

}

GLuint& const Texture::getTextureID(void)
{
	return textureID;

}
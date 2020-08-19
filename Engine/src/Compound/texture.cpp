#include "Texture.h"
#include "../Utilities/logger.h"
#include "../Manipulators/openGL.h"

// |*   Constructors   *|
Texture::Texture(const GLchar* dir)
{
	if(dir != nullptr)
		OpenGL::initTexture(dir, GtextureID, width, height);
	else
		OpenGL::initTexture(GtextureID, 1, width, height);

}

Texture::~Texture()
{
	glDeleteTextures(1, &GtextureID);
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

GLuint& const Texture::getGtextureID(void)
{
	return GtextureID;

}
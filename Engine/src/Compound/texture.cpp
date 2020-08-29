#include "Texture.h"
#include "../Utilities/logger.h"
#include "../Manipulators/openGL.h"

// |*   Constructors   *|
Texture::Texture(const GLchar* dir)
{
	if (dir != nullptr)
		init(dir);
	else
		init();

}

Texture::~Texture()
{
	glDeleteTextures(1, &GtextureID);
}


// |*   Functions   *|
void Texture::init(void)
{
	OpenGL::initTexture(GtextureID, 1, width, height);

}
void Texture::init(const char* dir)
{
	OpenGL::initTexture(dir, GtextureID, width, height);

}
void Texture::bind(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GtextureID);

}
bool Texture::isTexture(void)
{
	return glIsTexture(GtextureID);

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
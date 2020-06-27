#include "resourcesLoader.h"

void Utilities::ResourcesLoader::loadTexture(const char* path, GLuint &textureID) {

	glGenTextures(1, &textureID);

	CBitmap bitmap(path);

	//Create linnear filtered texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Apply texture wrapping horizontal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Apply texture wrapping along vertical (path?)

	//old school (minecrfat filtering)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //near filtering (for when texture needs to scale up when zoom in)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //far filtering (for when texture needs to scale down when zoom out)

	//bilinear filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //near filtering (for when texture needs to scale up when zoom in)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //far filtering (for when texture needs to scale down when zoom out)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

}
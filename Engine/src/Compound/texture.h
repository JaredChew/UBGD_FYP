#pragma once
#include <glad/glad.h>

class Texture {
private:
	GLuint textureID;
	int width;
	int height;

public:
	// |*   Constructors   *|
	Texture(const int& width, const int& height);
	Texture(const GLchar* dir);
	~Texture();


	// |*   Getters   *|
	const int& const getWidth(void);
	const int& const getHeight(void);
	GLuint& const getTextureID(void);

};
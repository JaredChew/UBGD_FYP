#pragma once
#include <glad/glad.h>
#include <SOIL2/SOIL2.h>

class Texture {
private:
	GLuint GtextureID;
	int width;
	int height;

public:
	// |*   Constructors   *|
	Texture(const GLchar* dir = nullptr);
	~Texture();


	// |*   Getters   *|
	const int& const getWidth(void);
	const int& const getHeight(void);
	GLuint& const getGtextureID(void);

};
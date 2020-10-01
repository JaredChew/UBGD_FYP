#pragma once
#include <glad/glad.h>

class Texture {
private:
	GLuint GtextureID;
	int width;
	int height;

public:
	// |*   Constructors   *|
	Texture(const GLchar* dir = nullptr);
	~Texture();


	// |*   Functions   *|
	void init(void);
	void init(const char* dir);
	void bind(void);
	bool isTexture(void);


	// |*   Getters   *|
	const int& const getWidth(void);
	const int& const getHeight(void);
	GLuint& const getGtextureID(void);

};
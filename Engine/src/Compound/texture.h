#pragma once
#include <glad/glad.h>

class Texture {
private:
	GLuint textureID;

	int width;
	int height;

	GLint internalFormat;
	GLenum format;

public:
	// |*   Constructors   *|
	Texture(const int& width, const int& height);
	Texture(const GLchar* dir);
	~Texture();


	operator bool() const;


	// |*   Getters   *|
	int& getWidth(void);
	int& getHeight(void);
	GLint& getInternalFormat();
	GLenum& getFormat();
	void setSize(const GLsizei& width, const GLsizei& height);
	GLuint& const getTextureID(void);

};
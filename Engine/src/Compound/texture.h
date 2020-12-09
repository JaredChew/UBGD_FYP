#pragma once
#include <glad/glad.h>
#include <string>

class Texture {
private:
	GLuint textureID;

	std::string path;

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
	std::string& const getPath();
	int& getWidth(void);
	int& getHeight(void);
	GLint& getInternalFormat();
	GLenum& getFormat();
	void setSize(const GLsizei& width, const GLsizei& height);
	GLuint& const getTextureID(void);

};
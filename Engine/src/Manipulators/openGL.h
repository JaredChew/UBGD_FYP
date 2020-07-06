#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>
#include <string>

namespace OpenGL {

	//static void error_callback(int error, const char* description);

	bool initProgramObject_Shader(GLuint &programID, const GLuint &fragmentShader, const GLuint &vertexShade);

	void initTexture(GLuint &textureID, const GLsizei &size, const GLuint &resolutionWidth, const GLuint &resolutionHeight);

	void initDepthBufferTexture(GLuint &textureID, const GLuint &resolutionWidth, const GLuint &resolutionHeight);

	bool checkIsFramebufferReady();

	GLuint loadShader(GLenum type, const char *shaderSrc);
	GLuint loadShaderFromFile(GLenum shaderType, std::string path);

	void loadTexture(const char *path, GLuint &textureID);
	void loadTexture(const void* image, GLuint& textureID, const GLuint& resolutionWidth, const GLuint& resolutionHeight);

	void loadCubemapTexture(std::vector<std::string> facesPath, const GLuint &textureID);

	void editTexel(const GLuint &textureID, const int &xOffset, const int &yOffset, const uint8_t &r, const uint8_t &g, const uint8_t &b);

}
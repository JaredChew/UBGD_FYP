#include "openGL.h"

#include "../Utilities/logger.h"

#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>

bool OpenGL::initProgramObject_Shader(GLuint &programID, const GLuint &fragmentShader, const GLuint &vertexShader) {

	GLuint programObject = glCreateProgram();

	if (programObject == 0) { return false; }

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	glBindAttribLocation(programObject, 0, "vPosition");
	glBindAttribLocation(programObject, 1, "vColor");
	glBindAttribLocation(programObject, 2, "vTexCoord");

	// Link the program
	glLinkProgram(programObject);

	GLint linked;

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) {

		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1) {

			char infoLog[1024];

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);

			Logger::getInstance()->warningLog("Failed to link shader program %s", static_cast<std::string>(infoLog));

		}

		glDeleteProgram(programObject);

		return false;
	}

	// Store the program object
	programID = programObject;

	glDetachShader(programID, fragmentShader);
	glDetachShader(programID, vertexShader);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	return true;

}

void OpenGL::initTexture(GLuint &textureID, const GLsizei &size, const GLuint &resolutionWidth, const GLuint &resolutionHeight) {

	glGenTextures(size, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGL::initTexture(const GLchar* dir, GLuint& textureID, GLint& width, GLint& height)
{
	int channels = 0;

	glGenTextures(1, &textureID);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = SOIL_load_image(dir, &width, &height, &channels, SOIL_LOAD_AUTO);

	glBindTexture(GL_TEXTURE_2D, textureID);

	if (0 == image)
	{
		std::string errorResult = SOIL_last_result();
		Logger::getInstance()->errorLog("SOIL loading error: $s", errorResult);

	}
	else
	{
		GLenum format = 0;

		switch (channels)
		{
		case SOIL_LOAD_L:
			format = GL_RED;
			break;

		case SOIL_LOAD_RGB:
			format = GL_RGB;
			break;

		case SOIL_LOAD_RGBA:
			format = GL_RGBA;
			break;
		}
		//glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_LINEAR); // magnifying = near, linear = gradient
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //GL_NEAREST); // minifying = far, nearest = more pixel
		//GL_NEAREST_MIPMAP_NEAREST

		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);

	}

	SOIL_free_image_data(image);

}

void OpenGL::initDepthBufferTexture(GLuint &textureID, const GLuint &resolutionWidth, const GLuint &resolutionHeight) {

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolutionWidth, resolutionHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

}

bool OpenGL::checkIsFramebufferReady() {

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {

		switch (status) {

			case GL_FRAMEBUFFER_UNDEFINED:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_UNDEFINED");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
				break;

			case GL_FRAMEBUFFER_UNSUPPORTED:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_UNSUPPORTED");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
				break;

		}

		return false;

	}

	return true;

}

GLuint OpenGL::loadShader(GLenum type, const char *shaderSrc) {

	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0) { return 0; }

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1) {

			char infoLog[4096];

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);

			Logger::getInstance()->warningLog("Failed to compile shader %s", static_cast<std::string>(infoLog));

		}

		glDeleteShader(shader);

		return 0;

	}

	return shader;

}

GLuint OpenGL::loadShaderFromFile(GLenum shaderType, std::string path) {

	GLuint shaderID = 0;

	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	if (sourceFile) {

		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());

		const GLchar *shaderSource = shaderString.c_str();

		return OpenGL::loadShader(shaderType, shaderSource);

	}
	else {

		Logger::getInstance()->warningLog("Unable to open file %s", path);

	}

	return shaderID;

}

/*
void OpenGL::loadTexture(const char *path, GLuint &textureID) 
{

	int resolutionWidth, resolutionHeight;

	unsigned char* image = SOIL_load_image(path, &resolutionWidth, &resolutionHeight, NULL, SOIL_LOAD_AUTO);

	//if(image) { printf("SOIL loading error: '%s'\n", SOIL_last_result()); }

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(image);

	delete image;
	image = nullptr;

}

void OpenGL::loadTexture(const void* image, GLuint& textureID, const GLuint& resolutionWidth, const GLuint& resolutionHeight) {

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

}
*/

void OpenGL::loadCubemapTexture(std::vector<std::string> facesPath, const GLuint &textureID) {

	unsigned char* image;

	int resolutionWidth, resolutionHeight;

	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < facesPath.size(); i++) {

		image = SOIL_load_image(facesPath[i].c_str(), &resolutionWidth, &resolutionHeight, NULL, SOIL_LOAD_AUTO);

		//if(image) { printf("SOIL loading error: '%s'\n", SOIL_last_result()); }

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, resolutionWidth, resolutionWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glDisable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete image;
	image = nullptr;

}

void OpenGL::editTexel(const GLuint &textureID, const int &xOffset, const int &yOffset, const uint8_t &r, const uint8_t &g, const uint8_t &b) {

	glBindTexture(GL_TEXTURE_2D, textureID);

	uint8_t data[3] = { r, g, b };

	glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

}
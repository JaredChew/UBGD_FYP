#include "openGL.h"

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

			Logger::getInstance()->warningLog(std::string("Failed to link shader program " + static_cast<std::string>(infoLog)));

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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glBindTexture(GL_TEXTURE_2D, 0);

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

			Logger::getInstance()->warningLog(std::string("Failed to compile shader " + static_cast<std::string>(infoLog)));

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

		Logger::getInstance()->warningLog(std::string("Unable to open file " + path));

	}

	return shaderID;

}

void OpenGL::loadTexture(const char *path, GLuint &textureID) {

	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGL::loadTexture(const char *path, GLuint &textureID, const GLuint &resolutionWidth, const GLuint &resolutionHeight, const GLuint &size) {

	CBitmap bitmap(path);

	glGenTextures(size, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGL::loadTexture(CBitmap &bitmap, GLuint &textureID) {

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGL::loadTexture(CBitmap &bitmap, GLuint &textureID, const GLuint &resolutionWidth, const GLuint &resolutionHeight, const GLuint &size) {

	glGenTextures(size, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGL::loadCubemapTexture(std::vector<std::string> facesPath, const GLuint &textureID) {

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < facesPath.size(); i++) {

		CBitmap bitmap(facesPath[i].c_str());

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glDisable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGL::editTexel(const GLuint &textureID, const int &xOffset, const int &yOffset, const uint8_t &r, const uint8_t &g, const uint8_t &b) {

	glBindTexture(GL_TEXTURE_2D, textureID);

	uint8_t data[3] = { r, g, b };

	glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

}
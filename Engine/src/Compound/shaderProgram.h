#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <string>

class Window;

class ShaderProgram {
private:
	GLuint m_programID;

public:
	// |*   Constructors   *|
	ShaderProgram();
	~ShaderProgram();


	// |*   Operators   *|
	void operator = (ShaderProgram* shader);


	// |*   Functions   *|
	bool init(std::string vertexDir, std::string fragmentDir);
	void use();
	bool isProgram();
	void deleteProgram();

	bool uniform_defaultImage(const std::string& uniformName = "sampler2d", const GLuint& index = 0);
	bool uniform_additionalImage(const std::string& uniformName, const GLuint& index, const GLuint& textureID);

	bool uniform_1int(const std::string& uniformName, const GLint& value);
	bool uniform_2int(const std::string& uniformName, const GLint& firstValue, const GLint& secondValue);
	bool uniform_3int(const std::string& uniformName, const GLint& firstValue, const GLint& secondValue, const GLint& thirdValue);
	bool uniform_4int(const std::string& uniformName, const GLint& firstValue, const GLint& secondValue, const GLint& thirdValue, const GLint& fourthValue);

	bool uniform_1int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer);
	bool uniform_2int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer);
	bool uniform_3int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer);
	bool uniform_4int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer);

	bool uniform_1float(const std::string& uniformName, const GLfloat& value);
	bool uniform_2float(const std::string& uniformName, const GLfloat& firstValue, const GLfloat& secondValue);
	bool uniform_3float(const std::string& uniformName, const GLfloat& firstValue, const GLfloat& secondValue, const GLfloat& thirdValue);
	bool uniform_4float(const std::string& uniformName, const GLfloat& firstValue, const GLfloat& secondValue, const GLfloat& thirdValue, const GLfloat& fourthValue);

	bool uniform_1float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer);
	bool uniform_2float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer);
	bool uniform_3float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer);
	bool uniform_4float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer);
	
	bool uniform_Matrix4fv(const std::string& uniformName, const glm::mat4x4& mvpMatrix);


	// |*   Getters   *|
	const GLuint& const getGprogramID() const;

public:
	// |*   Static Functions   *|
	static bool loadShaderCode(std::string& shaderCode, const std::string& shaderDir);
	static bool setShader(GLuint& shaderID, const GLenum& type, const GLchar* shaderCode);
	static bool setProgram(GLuint& programID, const GLuint* shaderIDs, const GLuint& size);
	static bool loadProgram(GLuint& programID, const std::string* shadersDir, const GLenum* shadersType, const GLuint& shadersSize);

	static GLint getUniformLocation(const GLuint& programID, const GLchar* uniformName);
};

#include "shaderProgram.h"

#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "texture.h"

//Shader shader[2];

// |*   Constructors   *|
ShaderProgram::ShaderProgram()
{
	m_programID = 0;
}
ShaderProgram::~ShaderProgram()
{
}


// |*   Operators   *|
void ShaderProgram::operator = (ShaderProgram* shader)
{
	m_programID = shader->getGprogramID();

}


// |*   Functions   *|
bool ShaderProgram::init(std::string vertexDir, std::string fragmentDir)
{
	GLuint GprogramID = 0;
	std::string shaderDirs[2] = { vertexDir, fragmentDir };
	GLenum shaderTypes[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	if(!loadProgram(GprogramID, shaderDirs, shaderTypes, 2) ) return false;

	// Store the program object
	m_programID = GprogramID;

	return true;
}
void ShaderProgram::use()
{
	glUseProgram(m_programID);
	
}
bool ShaderProgram::isProgram()
{
	return glIsProgram(m_programID);

}
void ShaderProgram::deleteProgram()
{
	 glDeleteProgram(m_programID);
}

bool ShaderProgram::uniform_Sampler(Texture& textureID, const std::string& uniformName, const GLuint& index)
{
	if (index < 32)
	{
		GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
		if (uniformLocation == -1) return false;

		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, textureID.getTextureID());

		glUniform1i(uniformLocation, index);

		glActiveTexture(GL_TEXTURE0);

		return true;
	}
	else
	{
		printf("Image index %u can not more than 31!!!\n", index);
		return false;

	}
}

bool ShaderProgram::uniform_Sampler(const GLuint& textureID, const std::string& uniformName, const GLuint& index)
{
	if (index < 32)
	{
		GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
		if (uniformLocation == -1) return false;

		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glUniform1i(uniformLocation, index);

		glActiveTexture(GL_TEXTURE0);

		return true;
	}
	else
	{
		printf("Image index %u can not more than 31!!!\n", index);
		return false;

	}

}

bool ShaderProgram::uniform_1int(const std::string& uniformName, const GLint& value)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform1i(uniformLocation, value);
	return true;

}
bool ShaderProgram::uniform_2int(const std::string& uniformName, const GLint& firstValue, const GLint& secondValue)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform2i(uniformLocation, firstValue, secondValue);
	return true;

}
bool ShaderProgram::uniform_3int(const std::string& uniformName, const GLint& firstValue, const GLint& secondValue, const GLint& thirdValue)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform3i(uniformLocation, firstValue, secondValue, thirdValue);
	return true;

}
bool ShaderProgram::uniform_4int(const std::string& uniformName, const GLint& firstValue, const GLint& secondValue, const GLint& thirdValue, const GLint& fourthValue)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform4i(uniformLocation, firstValue, secondValue, thirdValue, fourthValue);
	return true;

}

bool ShaderProgram::uniform_1int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform1iv(uniformLocation, size, pointer);
	return true;

}
bool ShaderProgram::uniform_2int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform2iv(uniformLocation, size, pointer);
	return true;

}
bool ShaderProgram::uniform_3int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform3iv(uniformLocation, size, pointer);
	return true;

}
bool ShaderProgram::uniform_4int_v(const std::string& uniformName, const GLsizei& size, const GLint* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform4iv(uniformLocation, size, pointer);
	return true;

}

bool ShaderProgram::uniform_1float(const std::string& uniformName, const GLfloat& value)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform1f(uniformLocation, value);
	return true;

}
bool ShaderProgram::uniform_2float(const std::string& uniformName, const GLfloat& firstValue, const GLfloat& secondValue)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform2f(uniformLocation, firstValue, secondValue);
	return true;

}
bool ShaderProgram::uniform_3float(const std::string& uniformName, const GLfloat& firstValue, const GLfloat& secondValue, const GLfloat& thirdValue)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform3f(uniformLocation, firstValue, secondValue, thirdValue);
	return true;

}
bool ShaderProgram::uniform_4float(const std::string& uniformName, const GLfloat& firstValue, const GLfloat& secondValue, const GLfloat& thirdValue, const GLfloat& fourthValue)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform4f(uniformLocation, firstValue, secondValue, thirdValue, fourthValue);
	return true;

}

bool ShaderProgram::uniform_1float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform1fv(uniformLocation, size, pointer);
	return true;

}
bool ShaderProgram::uniform_2float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform2fv(uniformLocation, size, pointer);
	return true;

}
bool ShaderProgram::uniform_3float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform3fv(uniformLocation, size, pointer);
	return true;

}
bool ShaderProgram::uniform_4float_v(const std::string& uniformName, const GLsizei& size, const GLfloat* pointer)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniform4fv(uniformLocation, size, pointer);
	return true;

}

bool ShaderProgram::uniform_Matrix4fv(const std::string& uniformName, const glm::mat4& matrix)
{
	GLuint uniformLocation = getUniformLocation(m_programID, uniformName.c_str());
	if (uniformLocation == -1) return false;

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	return true;

}


// |*   Getters   *|
const GLuint& const ShaderProgram::getGprogramID() const
{
	return m_programID;

}


// |*   Static Functions   *|
bool ShaderProgram::loadShaderCode(std::string& shaderCode, const std::string& shaderDir)
{
	std::ifstream sourceFile(shaderDir.c_str());

	if (!sourceFile)
	{
		printf("Unable to open file %s\n", shaderDir.c_str());

		return false;
	}

	shaderCode.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
	return true;

}
bool ShaderProgram::setShader(GLuint& shaderID, const GLenum& type, const GLchar* shaderCode)
{
	GLint success;

	shaderID = glCreateShader(type);
	if (!shaderID)
	{
		printf("Error to create shader!\n");
		return false;
	}

	glShaderSource(shaderID, 1, &shaderCode, NULL);

	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint infoLen = 0;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char infoLog[1024];
			glGetShaderInfoLog(shaderID, infoLen, NULL, infoLog);
			printf("Error compiling shader:\n%s\n", infoLog);

		}

		glDeleteShader(shaderID);
		return false;
	}

	return true;

}
bool ShaderProgram::setProgram(GLuint& programID, const GLuint* shaderIDs, const GLuint& size)
{
	GLint success;

	// Create the program object
	programID = glCreateProgram();

	if (programID == 0)
	{
		printf("Unable create program!\n");
		return false;
	}

	for (size_t i = 0; i < size; i++)
	{
		glAttachShader(programID, shaderIDs[i]);

		glDeleteShader(shaderIDs[i]);

	}

	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint infoLen = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char infoLog[1024];
			glGetProgramInfoLog(programID, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);

		}

		glDeleteProgram(programID);
		return false;

	}

	printf("Successful, set program ID \"%u\" completed!\n", programID);
	return true;

}
bool ShaderProgram::loadProgram(GLuint& programID, const std::string* shadersDir, const GLenum* shadersType, const GLuint& shadersSize)
{
	bool isSuccess = false;
	std::vector <std::string> shadersCode;
	std::vector <GLuint> shaderID;

	for (size_t i = 0; i < shadersSize; i++)
	{
		shadersCode.push_back(std::string());
		if (!loadShaderCode(shadersCode[i], shadersDir[i])) return false;

		shaderID.push_back(GLuint());
		if (!setShader(shaderID[i], shadersType[i], shadersCode[i].c_str()))  return false;
	}

	return setProgram(programID, shaderID.data(), shadersSize);
}

GLint ShaderProgram::getUniformLocation(const GLuint& programID, const GLchar* uniformName)
{
	GLint uniformLocation = glGetUniformLocation(programID, uniformName);

	if (uniformLocation == -1) 
		printf("Unable to get uniform %s location!\n", uniformName);

	return uniformLocation;
}

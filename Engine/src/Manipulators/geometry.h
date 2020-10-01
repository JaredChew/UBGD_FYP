#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Geometry {

	typedef void(*SetVertexArrayBufferFunction)(const GLuint& shaderProgramID, GLuint& vertexArrayObject, GLfloat* vertices, const GLuint& verticesSize, GLuint* indices, const GLuint& indicesSize);

	void drawTriangle(const GLuint &texture);
	void drawSquare(const GLuint &texture);
	void drawCircle(const GLuint &texture, const float &smoothness);
	//void drawStadium(const GLuint& texture, const float& smoothness);

	void drawPyramid(const GLuint &texture);
	void drawCube(const GLuint &texture);
	void drawSphere(const GLuint &texture, const float &smoothness);
	void drawCone(const GLuint &texture, const float &smoothness);
	void drawCylinder(const GLuint &texture, const float &smoothness);

	void drawSkyBox(const GLuint &texture);

	void setSquare(const GLuint& shaderProgramID, GLuint& vertexArrayObject, SetVertexArrayBufferFunction function);

	void setVertexArrayObject(const GLuint& shaderProgramID, GLuint& vertexArrayObject, GLfloat* vertices, const GLuint& verticesSize, GLuint* indices, const GLuint& indicesSize);
	
	void drawVertexArrayObject(GLuint& vertexArrayObject, const GLuint& indicesSize);

	static const GLuint& getSquareIndicesSize()
	{
		static GLuint indicesSize = 6;
		return indicesSize;
	};

}


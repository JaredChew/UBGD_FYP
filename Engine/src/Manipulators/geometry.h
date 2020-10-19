#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace Geometry {

	typedef void(*SetVertexArrayBufferFunction)(const GLuint& shaderProgramID, GLuint& vertexArrayObject, GLfloat* vertices, const GLuint& verticesSize, GLuint* indices, const GLuint& indicesSize);

	void squareLighting(GLuint& texture);

	void cudeLighting(GLuint& texture);

	void triangle(GLuint& texture);
	void square(GLuint& texture);
	void circle(GLuint& texture);

	void generateTriangleMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateSquareMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateCircleMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	//void generateStadiumMesh(const float& smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);

	void generatePyramidMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateSphereMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateConeMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateCylinderMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);

}


#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>

class Mesh {

public:
	static enum class DefaultGeometry { TRIANGLE, SQUARE, CIRCLE, STADIUM, PYRAMID, CUBE, SPHERE, CONE, CYLINDER };

private:
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

public:
	Mesh(const char* directory);
	Mesh(const DefaultGeometry& type);
	~Mesh();

	const GLuint& getVBO();
	const GLuint& getVAO();
	const GLuint& getEBO();

	const GLfloat* getVerticesData();
	const GLuint& getVerticesSize();
	const std::vector<GLfloat>& getVertices();

	const std::vector<GLuint>& getIndices();
	const GLuint& getIndicesSize();

};
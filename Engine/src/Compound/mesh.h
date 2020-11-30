#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>

struct VertexArrayObject;
struct Vertex;

class Mesh {
	
public:
	static enum class DefaultGeometry { TRIANGLE = 0, SQUARE, CIRCLE, STADIUM, PYRAMID, CUBE, SPHERE, CONE, CYLINDER, NONE };

private:
	Mesh::DefaultGeometry geometryType;

	VertexArrayObject* vao;
	//GLuint vertexArrayObject;
	//GLuint vertexBufferObject;
	//GLuint elementBufferObject;

	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;

public:
	Mesh(const char* directory);
	Mesh(const Mesh::DefaultGeometry& type);
	~Mesh();

	void setGeometryType(const Mesh::DefaultGeometry& geometryType);
	void setVertexArrayObject(VertexArrayObject* vertexArrayObject);
	
	const Mesh::DefaultGeometry& getGeometryType();

	VertexArrayObject* getVertexArrayObject();
	//const GLuint& getVBO();
	//const GLuint& getVAO();
	//const GLuint& getEBO();

	//const Vertex* getVerticesData();
	//const GLuint& getVerticesSize();
	//const std::vector<Vertex>& getVertices();

	//const std::vector<GLuint>& getIndices();
	//const GLuint& getIndicesSize();

};
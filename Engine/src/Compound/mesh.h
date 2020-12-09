#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>

struct VertexArrayObject;
struct Vertex;

class Mesh {
	
public:
	static enum class DefaultGeometry { RENDER_BOARD = 0, TRIANGLE, SQUARE, CIRCLE, STADIUM, PYRAMID, CUBE, SPHERE, CONE, CYLINDER, TORUS };

private:
	bool isCustom = false;
	VertexArrayObject* vao;

public:
	Mesh(VertexArrayObject* vertexArrayObject);
	Mesh(const Mesh::DefaultGeometry& type);
	~Mesh();

	void setGeometryType(const Mesh::DefaultGeometry& geometryType);
	void setVertexArrayObject(VertexArrayObject* vertexArrayObject);
	
	const bool& getIsCustom();
	VertexArrayObject* getVertexArrayObject();

};
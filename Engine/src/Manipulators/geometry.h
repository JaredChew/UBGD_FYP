#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

struct VertexArrayObject;

namespace Geometry {

	void generateRenderBoardMesh(VertexArrayObject*& vertexArrayObject);

	void generateTriangleMesh(VertexArrayObject*& vertexArrayObject);
	void generateSquareMesh(VertexArrayObject*& vertexArrayObject);
	void generateCircleMesh(VertexArrayObject*& vertexArrayObject);
	void generateStadiumMesh(VertexArrayObject*& vertexArrayObject);

	void generatePyramidMesh(VertexArrayObject*& vertexArrayObject);
	void generateCubeMesh(VertexArrayObject*& vertexArrayObject);
	void generateSphereMesh(VertexArrayObject*& vertexArrayObject);
	void generateConeMesh(VertexArrayObject*& vertexArrayObject);
	void generateCylinderMesh(VertexArrayObject*& vertexArrayObject);
	void generateTorusMesh(VertexArrayObject*& vertexArrayObject);

}


#include "mesh.h"

#include "../Manipulators/geometry.h"
#include "../Manipulators/system.h"

Mesh::Mesh(const char* directory) {

	//load vertices from file

	System::loadMesh(vertexBufferObject, elementBufferObject, vertexArrayObject, vertices.data(), vertices.size(), indices.data(), indices.size());

}

Mesh::Mesh(const DefaultGeometry& type) {

	switch (type) {

		case DefaultGeometry::TRIANGLE:
			Geometry::generateTriangleMesh(vertices, indices);
			break;

		case DefaultGeometry::SQUARE:
			Geometry::generateSquareMesh(vertices, indices);
			break;

		case DefaultGeometry::CIRCLE:
			Geometry::generateCircleMesh(100, vertices, indices);
			break;

		case DefaultGeometry::STADIUM:
			//Geometry::generateStadiumMesh(100, vertices, indices);
			break;

		case DefaultGeometry::PYRAMID:
			Geometry::generatePyramidMesh(vertices, indices);
			break;

		case DefaultGeometry::CUBE:
			Geometry::generateCubeMesh(vertices, indices);
			break;

		case DefaultGeometry::SPHERE:
			Geometry::generateSphereMesh(100, vertices, indices);
			break;

		case DefaultGeometry::CONE:
			Geometry::generateConeMesh(100, vertices, indices);
			break;

		case DefaultGeometry::CYLINDER:
			Geometry::generateCylinderMesh(100, vertices, indices);
			break;

	}

	System::loadMesh(vertexBufferObject, elementBufferObject, vertexArrayObject, vertices.data(), vertices.size(), indices.data(), indices.size());

}

Mesh::~Mesh() { }

const GLuint& Mesh::getVBO() {

	return vertexBufferObject;

}

const GLuint& Mesh::getVAO() {

	return vertexArrayObject;

}

const GLuint& Mesh::getEBO() {

	return elementBufferObject;

}

const GLfloat* Mesh::getVerticesData() {

	return vertices.data();

}

const GLuint& Mesh::getVerticesSize() {

	return vertices.size();

}

const std::vector<GLfloat>& Mesh::getVertices() {

	return vertices;

}

const std::vector<GLuint>& Mesh::getIndices() {

	return indices;

}

const GLuint& Mesh::getIndicesSize() {

	return indices.size();

}
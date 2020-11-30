#include "mesh.h"

#include "../Manipulators/geometry.h"
#include "../Manipulators/system.h"

#include "VertexArrayObject.h"

Mesh::Mesh(const char* directory) {

	//load vertices from file
	this->geometryType = Mesh::DefaultGeometry::NONE;
	
	vao = new VertexArrayObject();

	//vao->init(vertices.size(), vertices.data(), indices.size(), indices.data());

	//System::loadMesh(vertexBufferObject, elementBufferObject, vertexArrayObject, );

}

Mesh::Mesh(const Mesh::DefaultGeometry& type) {

	setGeometryType(type);

}

Mesh::~Mesh()
{ 
	VertexArrayObject* temp;
	Geometry::generateSquareMesh(temp);

	if (this->geometryType == Mesh::DefaultGeometry::NONE && vao != temp)
	{
		vao->clear();
		delete vao;
	}
}

void Mesh::setGeometryType(const Mesh::DefaultGeometry& type)
{
	this->geometryType = type;

	switch (type) {

	case DefaultGeometry::TRIANGLE:
		Geometry::generateTriangleMesh(vao);
		break;

	case DefaultGeometry::SQUARE:
		Geometry::generateSquareMesh(vao);
		break;

	case DefaultGeometry::CIRCLE:
		vao = new VertexArrayObject();
		//Geometry::generateCircleMesh(100, vertices, indices);
		break;

	case DefaultGeometry::STADIUM:
		vao = new VertexArrayObject();
		//Geometry::generateStadiumMesh(100, vertices, indices);
		break;

	case DefaultGeometry::PYRAMID:
		vao = new VertexArrayObject();
		//Geometry::generatePyramidMesh(vertices, indices);
		break;

	case DefaultGeometry::CUBE:
		Geometry::generateCubeMesh(vao);
		break;

	case DefaultGeometry::SPHERE:
		vao = new VertexArrayObject();
		//Geometry::generateSphereMesh(100, vertices, indices);
		break;

	case DefaultGeometry::CONE:
		vao = new VertexArrayObject();
		//Geometry::generateConeMesh(100, vertices, indices);
		break;

	case DefaultGeometry::CYLINDER:
		vao = new VertexArrayObject();
		//Geometry::generateCylinderMesh(100, vertices, indices);
		break;

	// User wrongly setup to model, just set it to default vao
	case DefaultGeometry::NONE:
		vao = new VertexArrayObject();
		//Geometry::generateSquareMesh(vao);
		break;


	}

}

void Mesh::setVertexArrayObject(VertexArrayObject* vertexArrayObject)
{
	this->geometryType = Mesh::DefaultGeometry::NONE;
	vao = vertexArrayObject;
}

const Mesh::DefaultGeometry& Mesh::getGeometryType()
{
	return geometryType;
}

VertexArrayObject* Mesh::getVertexArrayObject()
{
	return vao;
}

/*
const Vertex* Mesh::getVerticesData() {

	return vertices.data();

}

const GLuint& Mesh::getVerticesSize() {

	return vertices.size();

}

const std::vector<Vertex>& Mesh::getVertices() {

	return vertices;

}

const std::vector<GLuint>& Mesh::getIndices() {

	return indices;

}

const GLuint& Mesh::getIndicesSize() {

	return indices.size();

}
*/
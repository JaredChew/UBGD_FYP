#include "mesh.h"

#include "../Manipulators/geometry.h"
#include "../Manipulators/system.h"

#include "VertexArrayObject.h"

Mesh::Mesh(VertexArrayObject* vertexArrayObject) {
	
	isCustom = true;
	vao = vertexArrayObject;

}

Mesh::Mesh(const Mesh::DefaultGeometry& type) {

	setGeometryType(type);

}

Mesh::~Mesh()
{ 
	if (isCustom)
		delete vao;

}

void Mesh::setGeometryType(const Mesh::DefaultGeometry& type)
{
	if (isCustom)
		delete vao;

	isCustom = false;

	switch (type) {

	case DefaultGeometry::RENDER_BOARD:
		Geometry::generateRenderBoardMesh(vao);
		break;

	case DefaultGeometry::TRIANGLE:
		Geometry::generateTriangleMesh(vao);
		break;

	case DefaultGeometry::SQUARE:
		Geometry::generateSquareMesh(vao);
		break;

	case DefaultGeometry::CIRCLE:
		Geometry::generateCircleMesh(vao);
		break;

	case DefaultGeometry::STADIUM:
		Geometry::generateStadiumMesh(vao);
		break;

	case DefaultGeometry::PYRAMID:
		Geometry::generatePyramidMesh(vao);
		break;

	case DefaultGeometry::CUBE:
		Geometry::generateCubeMesh(vao);
		break;

	case DefaultGeometry::SPHERE:
		Geometry::generateSphereMesh(vao);
		break;

	case DefaultGeometry::CONE:
		Geometry::generateConeMesh(vao);
		break;

	case DefaultGeometry::CYLINDER:
		Geometry::generateCylinderMesh(vao);
		break;

	case DefaultGeometry::TORUS:
		Geometry::generateTorusMesh(vao);
		break;

	}

}

void Mesh::setVertexArrayObject(VertexArrayObject* vertexArrayObject)
{
	vao = vertexArrayObject;
}

const bool& Mesh::getIsCustom()
{
	return isCustom;
}

VertexArrayObject* Mesh::getVertexArrayObject()
{
	return vao;
}
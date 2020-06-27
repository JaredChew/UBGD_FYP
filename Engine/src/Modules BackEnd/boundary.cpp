#include "boundary.h"

Boundary::Boundary(Transform *const transform, const glm::vec4 &dimension, const BoundaryShape &type) : transform(transform) {

	w = dimension.x;
	h = dimension.y;
	d = dimension.z;
	r = dimension.w;

	centerOffset = glm::vec3(0.0f);

	this->type = type;

}

Boundary::~Boundary() { }

bool Boundary::withinBoundingCube(Boundary &boundary) {
	/*
	glm::vec4 dimenHalf = boundary.getDimension() / 2.0f;

	glm::vec3 startX = boundary.getCenterPoint() - dimenHalf;
	glm::vec3 endX = boundary.getCenterPoint() + dimenHalf;

	glm::vec3 startY = boundary.getCenterPoint() - dimenHalf;
	glm::vec3 endY = boundary.getCenterPoint() + dimenHalf;

	glm::vec3 startZ = boundary.getCenterPoint() - dimenHalf;
	glm::vec3 endZ = boundary.getCenterPoint() + dimenHalf;
	*/
	return false;

}

bool Boundary::withinBoundingBox(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingSphere(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingCircle(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingCylinder(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingCapsule(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingStadium(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingCone3D(Boundary &boundary) {

	return false;

}

bool Boundary::withinBoundingCone2D(Boundary &boundary) {

	return false;

}


void Boundary::setCenterOffset(const glm::vec3 &centerOffset) {

	this->centerOffset = centerOffset;

}

void Boundary::setBoundaryDimension(const glm::vec4 &dimension) {

	w = dimension.x;
	h = dimension.y;
	d = dimension.z;
	r = dimension.w;

}

void Boundary::setBoundaryShape(const BoundaryShape &type) {

	this->type = type;

}

glm::vec3 Boundary::getCenterOffset() {

	return centerOffset;

}

glm::vec4 Boundary::getDimension() {

	return glm::vec4(w, h, d, r);

}

Boundary::BoundaryShape Boundary::Boundary::getBoundaryShape() {

	return type;

}

glm::vec3 Boundary::getCenterPoint() {

	return transform->getPosition() + centerOffset;

}

bool Boundary::isColliding(Boundary &boundary) {

	switch (type) {

		case BoundaryShape::BOX:
			return withinBoundingBox(boundary);

		case BoundaryShape::CUBE:
			return withinBoundingCube(boundary);

		case BoundaryShape::CIRCLE:
			return withinBoundingCircle(boundary);

		case BoundaryShape::SPHERE:
			return withinBoundingSphere(boundary);

		case BoundaryShape::CAPSULE:
			return withinBoundingCapsule(boundary);

		case BoundaryShape::STADIUM:
			return withinBoundingStadium(boundary);

		case BoundaryShape::CONE_2D:
			return withinBoundingCone2D(boundary);

		case BoundaryShape::CONE_3D:
			return withinBoundingCone3D(boundary);

		case BoundaryShape::CYLINDER:
			return withinBoundingCylinder(boundary);

	}

	return false;

}

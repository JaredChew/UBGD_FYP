#include "collision.h"

#include "../Compound/transform.h"

#include <utility>

Collision::Collision(Transform* const transform, const glm::vec4& dimension, const BoundaryShape& type) : transform(transform) {

	boundary = dimension / 2.0f;

	centerOffset = glm::vec3(0.0f);

	this->type = type;

}

Collision::~Collision() { }

bool Collision::withinBoundingBox(Collision& collider) {

	int count = 0;

	if (getBoundaryWidth().y >= collider.getBoundaryWidth().x) { ++count; }
	if (getBoundaryWidth().x >= collider.getBoundaryWidth().y) { ++count; }

	if (getBoundaryHeight().y >= collider.getBoundaryHeight().x) { ++count; }
	if (getBoundaryHeight().x >= collider.getBoundaryHeight().y) { ++count; }

	return !count;

}

bool Collision::withinBoundingCube(Collision& collider) {

	int count = 0;

	if (getBoundaryWidth().y >= collider.getBoundaryWidth().x) { ++count; }
	if (getBoundaryWidth().x >= collider.getBoundaryWidth().y) { ++count; }

	if (getBoundaryHeight().y >= collider.getBoundaryHeight().x) { ++count; }
	if (getBoundaryHeight().x >= collider.getBoundaryHeight().y) { ++count; }

	if (getBoundaryDepth().y >= collider.getBoundaryDepth().x) { ++count; }
	if (getBoundaryDepth().x >= collider.getBoundaryDepth().y) { ++count; }

	return !count;

}

bool Collision::withinBoundingCircle(Collision& collider) {

	int count = 0;

	//

	return !count;

}

bool Collision::withinBoundingSphere(Collision& collider) {

	int count = 0;

	//

	return !count;

}

bool Collision::withinBoundingStadium(Collision& collider) {

	int count = 0;

	//

	return !count;

}

bool Collision::withinBoundingCapsule(Collision& collider) {

	int count = 0;

	//

	return !count;

}

void Collision::setCenterOffset(const glm::vec3& centerOffset) {
	this->centerOffset = centerOffset;
}

void Collision::setBoundaryDimension(const glm::vec4& dimension) {
	boundary = dimension / 2.0f;
}

void Collision::setBoundaryShape(const BoundaryShape& type) {
	this->type = type;
}

glm::vec3& const Collision::getCenterOffset() {
	return centerOffset;
}

glm::vec2& const Collision::getBoundaryWidth() {

	glm::vec3 boundaryPosition = transform->getPosition() + centerOffset;

	return glm::vec2(boundary.x - boundaryPosition.x, boundary.x + boundaryPosition.x);

}

glm::vec2& const Collision::getBoundaryHeight() {

	glm::vec3 boundaryPosition = transform->getPosition() + centerOffset;

	return glm::vec2(boundary.y - boundaryPosition.y, boundary.y + boundaryPosition.y);

}

glm::vec2& const Collision::getBoundaryDepth() {

	glm::vec3 boundaryPosition = transform->getPosition() + centerOffset;

	return glm::vec2(boundary.z - boundaryPosition.z, boundary.z + boundaryPosition.z);

}

glm::vec2& const Collision::getBoundaryRadius() {

	return glm::vec2();

}

glm::vec4& const Collision::getBoundaryDimension() {
	return boundary * 2.0f;
}

Collision::BoundaryShape& const Collision::getBoundaryShape() {
	return type;
}

glm::vec3& const Collision::getCenterPoint() {
	return transform->getPosition() + centerOffset;
}

bool Collision::isColliding(Collision& collider) {

	switch (type) {

	case BoundaryShape::BOX:
		return withinBoundingBox(collider);

	case BoundaryShape::CUBE:
		return withinBoundingCube(collider);

	case BoundaryShape::CIRCLE:
		return withinBoundingCircle(collider);

	case BoundaryShape::SPHERE:
		return withinBoundingSphere(collider);

	case BoundaryShape::CAPSULE:
		return withinBoundingCapsule(collider);

	case BoundaryShape::STADIUM:
		return withinBoundingStadium(collider);

	}

	return false;

}

void update() {

	//if collide then put position right before colliding

}
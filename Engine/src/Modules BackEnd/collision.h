#pragma once

#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

class Transform;

class Collision {

private:

	Transform* const transform;

public:

	enum class BoundaryShape { BOX, CUBE, RADIUS }; //, STADIUM, CAPSULE

private:

	BoundaryShape type;

	glm::vec4 boundary;
	glm::vec3 centerOffset;

	int entityCollidedID;

private:

	//element 1 is -x, element 2 is +x
	glm::vec2& const getBoundaryWidth();
	glm::vec2& const getBoundaryHeight();
	glm::vec2& const getBoundaryDepth();

	float& const getBoundaryRadius();

	bool withinBoundingBox(Collision& boundary);
	//bool withinBoundingStadium(Collision& boundary);

	bool withinBoundingCube(Collision& boundary);
	//bool withinBoundingCapsule(Collision& boundary);

	bool withinBoundingRadius(Collision& boundary);

public:

	Collision(Transform* const transform, const glm::vec4& dimension = glm::vec4(1.0f), const BoundaryShape& type = BoundaryShape::BOX);
	~Collision();

	void setCenterOffset(const glm::vec3& centerOffset);
	void setBoundaryDimension(const glm::vec4& dimension);
	void setBoundaryShape(const BoundaryShape& type);

	glm::vec4& const getBoundaryDimension();
	glm::vec3& const getCenterPoint();
	glm::vec3& const getCenterOffset();

	BoundaryShape& const getBoundaryShape();

	bool isColliding(Collision& boundary);

};
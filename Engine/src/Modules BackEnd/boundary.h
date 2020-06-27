#pragma once

#include <utility>

#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include "../Compound/transform.h"

class Boundary {

private:

	Transform *const transform;

public:

	enum class BoundaryShape { BOX, CUBE, CIRCLE, SPHERE, CAPSULE, STADIUM, CONE_2D, CONE_3D, CYLINDER };

private:

	BoundaryShape type;

	glm::vec3 centerOffset;

	float w;
	float h;
	float d;
	float r;

private:

	bool withinBoundingCube(Boundary &boundary);
	bool withinBoundingBox(Boundary &boundary);

	bool withinBoundingSphere(Boundary &boundary);
	bool withinBoundingCircle(Boundary &boundary);

	bool withinBoundingCylinder(Boundary &boundary);

	bool withinBoundingCapsule(Boundary &boundary);
	bool withinBoundingStadium(Boundary &boundary);

	bool withinBoundingCone3D(Boundary &boundary);
	bool withinBoundingCone2D(Boundary &boundary);

public:

	Boundary(Transform *const transform, const glm::vec4 &dimension = glm::vec4(1.0f), const BoundaryShape &type = BoundaryShape::BOX);
	~Boundary();

	void setCenterOffset(const glm::vec3 &centerOffset);
	void setBoundaryDimension(const glm::vec4 &dimension);
	void setBoundaryShape(const BoundaryShape &type);

	glm::vec3 getCenterOffset();
	glm::vec4 getDimension();

	BoundaryShape getBoundaryShape();

	glm::vec3 getCenterPoint();

	bool isColliding(Boundary &boundary);

};
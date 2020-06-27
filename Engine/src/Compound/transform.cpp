#include "transform.h"

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &dimension) {

	this->position = position;
	this->rotation = rotation;
	this->dimension = dimension;

	pivotPoint = glm::vec3(0.0f);

	rotationLocal = glm::vec3(0.0f);
	dimensionLocal = glm::vec3(1.0f);

	modelMatrix = glm::mat4(1.0f);

	isModelMatrixOld = true;

}

Transform::~Transform() { }

void Transform::updateModelMatrix() {

	if (!isModelMatrixOld) { return; }

	modelMatrix =

		glm::scale(glm::mat4(1.0f), glm::vec3(dimensionLocal)) *
		
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
		
		glm::translate(glm::mat4(1.0f), glm::vec3(position)) *

		glm::rotate(glm::mat4(1.0f), glm::radians(rotationLocal.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotationLocal.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotationLocal.z), glm::vec3(0.0f, 0.0f, 1.0f)) *

		glm::scale(glm::mat4(1.0f), glm::vec3(dimensionLocal)) *

		glm::translate(glm::mat4(1.0f), glm::vec3(pivotPoint));

	isModelMatrixOld = false;

}

void Transform::setPivotPoint(const glm::vec3 &pivotPoint) {

	this->pivotPoint = pivotPoint;

	isModelMatrixOld = true;

}

void Transform::setPosition(const glm::vec3 &position) {

	this->position = position;

	isModelMatrixOld = true;

}

void Transform::setRotation(const glm::vec3 &rotation) {

	this->rotation = rotation;

	isModelMatrixOld = true;

}

void Transform::setRotationLocal(const glm::vec3 &rotation) {

	rotationLocal = rotation;

	isModelMatrixOld = true;

}

void Transform::setDimension(const glm::vec3 &dimension) {

	this->dimension = dimension;

	isModelMatrixOld = true;

}

void Transform::setDimensionLocal(const glm::vec3 &dimension) {

	dimensionLocal = dimension;

	isModelMatrixOld = true;

}

void Transform::setTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &dimension) {

	this->position = position;
	this->rotation = rotation;
	this->dimension = dimension;

	isModelMatrixOld = true;

}

void Transform::translate(const glm::vec3 &translate) {

	position += translate;

	isModelMatrixOld = true;

}

void Transform::rotate(const glm::vec3 &rotate) {

	rotation += rotate;

	isModelMatrixOld = true;

}

void Transform::scale(const glm::vec3 &scale) {

	dimension += scale;

	isModelMatrixOld = true;

}

void Transform::transform(const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale) {

	position += translate;
	rotation += rotate;
	dimension += scale;

	isModelMatrixOld = true;

}

void Transform::rotateLocal(const glm::vec3 &rotate) {

	rotationLocal += rotate;

	isModelMatrixOld = true;

}

void Transform::scaleLocal(const glm::vec3 &scale) {

	dimensionLocal += scale;

	isModelMatrixOld = true;

}

void Transform::transformLocal(const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale) {

	position += translate;
	rotationLocal += rotate;
	dimensionLocal += scale;

	isModelMatrixOld = true;

}

glm::vec3 Transform::getPosition() {
	return position;
}

glm::vec3 Transform::getRotation() {
	return rotation;
}

glm::vec3 Transform::getRotationLocal() {
	return rotationLocal;
}

glm::vec3 Transform::getDimension() {
	return dimension;
}

glm::vec3 Transform::getDimensionLocal() {
	return dimensionLocal;
}

glm::vec3 Transform::getPivotPoint() {
	return pivotPoint;
}

glm::mat4 Transform::getModelMatrix() {

	updateModelMatrix();

	return modelMatrix;

}

float *Transform::getModelMatrixData() {
	return glm::value_ptr(modelMatrix);
}

//			BACKUP			//

/*

#include "transform.h"

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &dimension) { //, const glm::vec3& pivotPoint

	this->position = position;
	this->rotation = rotation;
	this->dimension = dimension;
	//this->pivotPoint = pivotPoint;

	orientation = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);

	updateModelMatrix = true;

}

Transform::~Transform() { }

void Transform::setPosition(const glm::vec3 &position) {
	this->position = position;
	updateModelMatrix = true;
}

void Transform::setRotation(const glm::vec3 &rotation) {
	this->rotation = rotation;
	updateModelMatrix = true;
}

void Transform::setDimension(const glm::vec3 &dimension) {
	this->dimension = dimension;
	updateModelMatrix = true;
}

void Transform::setTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &dimension) {

	this->position = position;
	this->rotation = rotation;
	this->dimension = dimension;

	updateModelMatrix = true;

}

void Transform::translate(const glm::vec3 &translate) {
	position += translate;
	updateModelMatrix = true;
}

void Transform::rotate(const glm::vec3 &rotate) {

	orientation = ( glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(1.0f, 0.0f, 1.0f)) ) *

		orientation;

	rotation += rotate;

	updateModelMatrix = true;

}

void Transform::scale(const glm::vec3 &scale) {
	dimension += scale;
	updateModelMatrix = true;
}

void Transform::transform(const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale) {

	Transform::translate(translate);
	Transform::rotate(rotate);
	Transform::scale(dimension += scale);

	updateModelMatrix = true;

}

void Transform::translateLocal(const glm::vec3 &translate) {

	this->position += glm::vec3(orientation * glm::vec4(translate.x, translate.y, translate.z, 1.0f));

	updateModelMatrix = true;

}

void Transform::rotateLocal(const glm::vec3 &rotate) {

	orientation = orientation *

		( glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		  glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		  glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(1.0f, 0.0f, 1.0f)) );

	rotation += rotate;

	updateModelMatrix = true;

}

void Transform::transformLocal(const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale) {

	translateLocal(translate);
	rotateLocal(rotate);
	Transform::scale(scale);

	updateModelMatrix = true;

}

glm::vec3 Transform::getPosition() {
	return position;
}

glm::vec3 Transform::getRotation() {
	return rotation;
}

glm::vec3 Transform::getDimension() {
	return dimension;
}

glm::mat4 Transform::getOrientation() {
	return orientation;
}

glm::mat4 Transform::getModelMatrix() {

	if (updateModelMatrix) { modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z)) * orientation * glm::scale(glm::mat4(1.0f), dimension); }

	updateModelMatrix = false;

	return modelMatrix;

}

float *Transform::getModelMatrixData() {
	return glm::value_ptr(modelMatrix);
}


*/
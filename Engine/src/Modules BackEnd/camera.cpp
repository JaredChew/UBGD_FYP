#include "camera.h"

#include "../Compound/transform.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &dimension) {

	transform = new Transform(position, rotation, dimension);

	projectionMatrix = glm::mat4(1.0f);
	orientation = glm::mat4(1.0f);

	projectionType = NONE;
}

Camera::~Camera() { }

void Camera::setProjectionPerspective(const float& fov, const float& windowRatio, const float& near, const float& far) {

	projectionMatrix = glm::perspective<float>(glm::radians(fov), windowRatio, near, far);
	projectionType = PERSPECTIVE;

}

void Camera::setProjectionOrthographic(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far) {

	projectionMatrix = glm::ortho<float>(left, right, bottom, top, near, far);
	projectionType = ORTHOGRAPHIC;

}

glm::mat4& const Camera::getOrientation() {
	return orientation;
}

const glm::mat4& const Camera::getViewMatrix() {

	return  transform->getModelMatrix(); //glm::inverse(viewMatrix)

}

const glm::mat4& const Camera::getViewMatrixWithoutTranslate() {

	return glm::mat4(

		glm::rotate(glm::mat4(1.0f), glm::radians(transform->getRotationLocal().x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(transform->getRotationLocal().y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(transform->getRotationLocal().z), glm::vec3(0.0f, 0.0f, 1.0f))

	);

}

void Camera::update(const int& height, const int& width, const float& fov)
{
	if (projectionType != ORTHOGRAPHIC) return;

	float w = 0.0f, h = 0.0f;
	float winH = static_cast<float>(height), winW = static_cast<float>(width);
	if (winH < winW)
	{
		w = 0.1f * fov;
		h = 0.1f * winH / winW * fov;
	}
	else if (winH > winW)
	{
		w = 0.1f * winW / winH * fov;
		h = 0.1f * fov;
	}
	else
	{
		w = 0.1f * fov;
		h = 0.1f * fov;
	}

	setProjectionOrthographic(-w, w, -h, h, 0.1f, 3000.0f);

}

glm::mat4& const Camera::getProjectionMatrix() {
	return projectionMatrix;
}

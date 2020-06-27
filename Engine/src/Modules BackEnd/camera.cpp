#include "camera.h"

Camera::Camera(Window *const wnd, Keyboard *const kbd, Mouse *const mse, const float &cameraSpeed, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension) : wnd(wnd), kbd(kbd), mse(mse) {

	this->position = position;
	this->rotation = rotation;
	this->dimension = dimension;

	this->cameraSpeed = cameraSpeed;

	projectionMatrix = glm::mat4(1.0f);

	viewMatrix = glm::mat4(1.0f);
	orientation = glm::mat4(1.0f);

	updateViewMatrix = true;

	renderWidth = wnd->getWidth();
	renderHeight = wnd->getWidth();
	renderRatio = renderWidth / renderHeight;

	renderQuality = 100.0f;

}

Camera::~Camera() { }

void Camera::translate(const glm::vec3 &translate) {
	position += glm::vec3(-translate.x, translate.y, translate.z);
	updateViewMatrix = true;
}

void Camera::rotate(const glm::vec3 &rotate) {

	orientation = (glm::rotate(glm::mat4(1.0f), glm::radians(-rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(1.0f, 0.0f, 1.0f))) *

		orientation;

	rotation += rotate;

	updateViewMatrix = true;

}

void Camera::scale(const glm::vec2 &scale) {
	dimension += scale;
	updateViewMatrix = true;
}

void Camera::translateLocal(const glm::vec3 &translate) {

	this->position += glm::vec3(orientation * glm::vec4(-translate.x, translate.y, translate.z, 1.0f));

	updateViewMatrix = true;

}

void Camera::rotateLocal(const glm::vec3 &rotate) {

	orientation = orientation *
		(glm::rotate(glm::mat4(1.0f), glm::radians(-rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		 glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		 glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(1.0f, 0.0f, 1.0f)));

	rotation += rotate;

	updateViewMatrix = true;

}

void Camera::setPosition(const glm::vec3 &position) {
	this->position = position;
	updateViewMatrix = true;
}

void Camera::setRotation(const glm::vec3 &rotation) {
	this->rotation = rotation;
	updateViewMatrix = true;
}

void Camera::setDimension(const glm::vec2 &dimension) {
	this->dimension = dimension;
	updateViewMatrix = true;
}

void Camera::setPlot(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension) {

	this->position = position;
	this->rotation = rotation;
	this->dimension = dimension;

	updateViewMatrix = true;

}

void Camera::setSpeed(const float &cameraSpeed) {
	this->cameraSpeed = cameraSpeed;
	updateViewMatrix = true;
}

void Camera::setRenderQuality(const int &renderQuality) {

	this->renderQuality = renderQuality;

	if (this->renderQuality <= 0) { this->renderQuality = 1; }

	renderWidth = renderWidth * (renderQuality / 100);
	renderHeight = renderHeight * (renderQuality / 100);

	renderRatio = renderWidth / renderHeight;

}

void Camera::unlockedControls() {

	if (!kbd->isPressed('Z')) { return; }

	//move
	if (mse->isPressed(MOUSE_BUTTON_MIDDLE)) {

		translate(glm::vec3(mse->getPositionOffset().x * 0.01f, -mse->getPositionOffset().y * 0.01f, 0.0f));
		//translateLocal(glm::vec3(mse->getPositionOffset().x * 0.01f, -mse->getPositionOffset().y * 0.01f, 0.0f));

	}

	//zoom
	if (mse->getScrollDirection() != 0.0) { position.z -= mse->getScrollDirection() * 2.5f; }

	//rotate
	if (mse->isPressed(MOUSE_BUTTON_RIGHT)) {

		rotate(glm::vec3(0.0f, mse->getPositionOffset().x * 0.1f, 0.0f));
		rotateLocal(glm::vec3(mse->getPositionOffset().y * -0.1f, 0.0f, 0.0f));

	}

	updateViewMatrix = true;

}

void Camera::update() {

	if (ENABLE_FREE_MOVEMENT) { unlockedControls(); }

}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getRotation() {
	return rotation;
}

glm::vec2 Camera::getDimension() {
	return dimension;
}

glm::mat4 Camera::getOrientation() {
	return orientation;
}

float Camera::getSpeed() {
	return cameraSpeed;
}

int Camera::getRenderWidth() {
	return renderWidth;
}

int Camera::getRenderHeight() {
	return renderHeight;
}

int Camera::getRenderQuality() {
	return renderQuality;
}

float Camera::getRenderRatio() {
	return renderRatio;
}

glm::mat4 Camera::getViewMatrix() {

	if (updateViewMatrix) { viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, position.y, -position.z)) * orientation * glm::scale(glm::mat4(1.0f), glm::vec3(dimension.x, dimension.y, 0.0f)); }
	//if (updateViewMatrix) { viewMatrix = orientation * glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, -position.z)) * glm::scale(glm::mat4(1.0f), dimension); }

	updateViewMatrix = false;

	return  viewMatrix; //glm::inverse(viewMatrix)

}

glm::mat4 Camera::getViewMatrixWithoutTranslate() {

	return glm::mat4(

		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))

	);

}

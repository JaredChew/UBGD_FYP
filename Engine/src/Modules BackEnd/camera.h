#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "mouse.h"
#include "keyboard.h"

#define ENABLE_FREE_MOVEMENT true

class Camera {

private:

	Window *const wnd;
	Keyboard *const kbd;
	Mouse *const mse;

private:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec2 dimension;

	glm::mat4x4 viewMatrix;
	glm::mat4x4 orientation;

	float cameraSpeed;

	bool updateViewMatrix;

	int renderWidth;
	int renderHeight;
	int renderRatio;

	float renderQuality;

public:

	glm::mat4 projectionMatrix;

private:

	void unlockedControls();

public:

	Camera(Window *const wnd, Keyboard *const kbd, Mouse *const mse, const float &cameraSpeed, const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f), const glm::vec2 &dimension = glm::vec2(1.0f));
	~Camera();

	void translate(const glm::vec3 &translate);
	void rotate(const glm::vec3 &rotate);
	void scale(const glm::vec2 &scale);

	void translateLocal(const glm::vec3 &translate);
	void rotateLocal(const glm::vec3 &rotate);

	void setPosition(const glm::vec3 &position);
	void setRotation(const glm::vec3 &rotation);
	void setDimension(const glm::vec2 &dimension);

	void setPlot(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension);

	void setSpeed(const float &cameraSpeed);
	void setRenderQuality(const int &renderQuality);

	void update();

	float getSpeed();

	int getRenderWidth();
	int getRenderHeight();
	int getRenderQuality();

	float getRenderRatio();

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec2 getDimension();

	glm::mat4 getOrientation();

	glm::mat4 getViewMatrix();
	glm::mat4 getViewMatrixWithoutTranslate();

};

/*

	// ** FPS camera ** /

	if (!kbd->isPressed('Z')) { return; }

	//move
	if (mse->isPressed(MOUSE_BUTTON_MIDDLE)) {

		translateLocal(glm::vec3(mse->getPositionOffset().x * 0.01f, -mse->getPositionOffset().y * 0.01f, 0.0f));

	}

	//zoom
	if (mse->getScrollDirection() != 0.0) { position.z -= mse->getScrollDirection() * 2.5f; }

	//rotate
	if (mse->isPressed(MOUSE_BUTTON_RIGHT)) {

		rotate(glm::vec3(0.0f, mse->getPositionOffset().x * 0.1f, 0.0f));
		rotateLocal(glm::vec3(mse->getPositionOffset().y * 0.1f, 0.0f, 0.0f));

	}

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, -position.z)) * orientation;

	glm::inverse(viewMatrix);

/*

void Camera::update() {

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, -position.z)) *

		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		//glm::scale(glm::mat4(1.0f), glm::vec3(dimension.x, dimension.y, 0.0f));


	//glm method
	//glm::vec3 Pos(3.0f, 7.0f, -10.0f);
	//glm::vec3 Target(0.0f, -0.2f, 1.0f);
	//glm::vec3 Up(0.0, 1.0f, 0.0f);

	//glm::lookAt(Pos, Target, Up);


}

*/
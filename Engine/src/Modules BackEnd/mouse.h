#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/vec2.hpp>

#include "window.h"

#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_3

class Mouse {

private:

	Window *const wnd;

private:

	enum class ButtonState { CLEAR = -1, RELEASE = GLFW_RELEASE, PRESS = GLFW_PRESS, HOLD = GLFW_REPEAT };

	static glm::vec2 position;
	static glm::vec2 positionOffset;
	static glm::vec2 positionDirection;

	static double scrollValue;
	static double scrollOffset;

	static int scrollDirection;

	static int buttonPressStatus[3];

private:

	static void onMouseMove(GLFWwindow *wnd, double x, double y);
	static void onMouseWheelScroll(GLFWwindow *window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

public:

	Mouse(Window *wnd);
	~Mouse();

	bool isPressed(const int &button);
	bool isPressedOnce(const int &button);
	bool isReleased(const int &button);
	bool isHold(const int &button);

	void postUpdate();
	void preUpdate();

	glm::vec2 getPosition();
	glm::vec2 getPositionOffset();
	glm::vec2 getPositionDirection();

	double getScrollValue();
	double getOffsetScrol();

	int getScrollDirection();

};
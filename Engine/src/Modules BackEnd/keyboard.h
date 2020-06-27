#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "window.h"

#define SET_1_KEYS_START 32
#define SET_2_KEYS_START 161

#define SET_1_KEYS_END 96
#define SET_2_KEYS_END 348

#define SET_1_KEYS SET_1_KEYS_END - SET_1_KEYS_START
#define SET_2_KEYS SET_2_KEYS_END - SET_2_KEYS_START

class Keyboard {

private:

	Window *const wnd;

private:

	enum class KeyState { CLEAR = -1, RELEASE, PRESS, HOLD };

	static int keyPressStatus_set1[SET_1_KEYS];
	static int keyPressStatus_set2[SET_2_KEYS];

	bool returnStatus;

private:

	static void setKeyPressStatus(const char &key, const int &state);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

	bool isKeyValid(const char &key);

	int getKeyPressStatus(const char &key);

public:
	Keyboard(Window *const wnd);
	~Keyboard();

	bool isPressed(const char &key);
	bool isPressedOnce(const char &key);
	bool isReleased(const char &key);
	bool isHold(const char &key);

	void postUpdate();

};
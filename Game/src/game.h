#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"
#include "Modules BackEnd/mouse.h"

#include "Specification/session.h"

#include "defaultSettings.h"

class Game {

private:

	Window *const wnd;

private:

	Keyboard *kbd;
	Mouse *mse;

	Camera *camera;

	Session *session;

public:
	Game(Window *const wnd);
	~Game();

	void initSessionState();

	void gameLoop();

};
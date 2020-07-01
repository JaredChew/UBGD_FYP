#define GLFW_INCLUDE_NONE 1
#define GLFW_DLL 1

//#define GL_GLEXT_PROTOTYPES

#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <cstdlib> 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utilities/logger.h"
#include "Modules BackEnd/window.h"

#include "game.h"
#include "defaultSettings.h"

static void error_callback(int error, const char *description) {
	Logger::getInstance()->customLog("GLFW ERROR", description);

}

int main(void) {

	Window *wnd;

	Game *game;

	Logger::init(WINDOW_TITLE, VERSION, true);

	glfwSetErrorCallback(error_callback);

	//Initialize GLFW library
	if (!glfwInit()) {

		Logger::getInstance()->errorLog("Failed to initialise GLFW");

		return -1;

	}

	//Set window hints
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	//Create and open a window
	wnd = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 0, NULL);

	if (!wnd->successfulCreation()) {

		Logger::getInstance()->errorLog("glfwCreateWindow Error");

		glfwTerminate();

		return -1;

	}

	glfwMakeContextCurrent(wnd->getWindow());

	wnd->setVsync(VSYNC);
	wnd->setFpsLimit(MAX_FPS);
	wnd->setDisplayFps(DISPLAY_FPS);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::getInstance()->errorLog("Failed to initialize OpenGL context");
		return -1;
	}

	Logger::getInstance()->infoLog((char *)glGetString(GL_VERSION));
	Logger::getInstance()->infoLog(glfwGetVersionString());

	if (!GLAD_GL_VERSION_3_2) {

		Logger::getInstance()->errorLog("Your device must support OpenGL 3.2+");

		delete wnd;
		wnd = nullptr;

		glfwTerminate();

		return -1;

	}

	game = new Game(wnd);

	//Window loop
	while (!glfwWindowShouldClose(wnd->getWindow())) {

		game->gameLoop();

		//wnd->recordTock();
		wnd->update();
		//wnd->recordTick();

		//Swap front and back buffer
		glfwSwapBuffers(wnd->getWindow());

		//Get window and input events
		glfwPollEvents();

	}

	delete game;
	game = nullptr;

	glfwTerminate();

	exit(EXIT_SUCCESS);

}
#define GLFW_INCLUDE_NONE 1
#define GLFW_DLL 1
//#define GL_GLEXT_PROTOTYPES

#include "defaultSettings.h"
#include "global.h"

#include "game.h"

#include "Manipulators/system.h"
#include "Utilities/logger.h"

#if  _DEBUG

#include <Windows.h>

	void runDebugTools() {

		STARTUPINFO startInfo = { 0 };
		PROCESS_INFORMATION processInfo = { 0 };

		//ShellExecuteA(NULL, NULL, "Tracy/Tracy.exe", NULL, NULL, SW_SHOW);
		BOOL succes = CreateProcess(TEXT("..\\Tools\\Tracy\\Tracy.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startInfo, &processInfo);

		Logger::getInstance()->debugLog(succes ? "Tracy has started" : "Tracy has failed to start");

	}

#else

void runDebugTools() {  }

#endif

static void error_callback(int error, const char* description) {
	Logger::getInstance()->customLog("GLFW ERROR", description);

}

int main(void) {

	Logger::init(WINDOW_TITLE, VERSION, true);

	//runDebugTools();

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
	Global::window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 0, NULL);

	if (!Global::window->successfulCreation()) {

		Logger::getInstance()->errorLog("glfwCreateWindow Error");

		glfwTerminate();

		return -1;

	}

	glfwMakeContextCurrent(Global::window->getWindow());

	Global::window->setVsync(VSYNC);
	Global::window->setFpsLimit(MAX_FPS);
	Global::window->setDisplayFps(DISPLAY_FPS);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::getInstance()->errorLog("Failed to initialize OpenGL context");
		return -1;
	}

	Logger::getInstance()->infoLog((char*)glGetString(GL_VERSION));
	Logger::getInstance()->infoLog(glfwGetVersionString());

	if (!GLAD_GL_VERSION_3_2) {

		Logger::getInstance()->errorLog("Your device must support OpenGL 3.2+");

		delete Global::window;
		Global::window = nullptr;

		glfwTerminate();

		return -1;

	}

	Global::deltaTime = new Timer();

	Game* game = new Game();

	Global::applicationRunning = true;

	//Window loop
	while (Global::applicationRunning) {

		game->gameLoop();

		Global::deltaTime->recordTick();
		Global::window->update(Global::deltaTime->getDeltaTime());
		Global::deltaTime->recordTock();

	}

	delete game;
	game = nullptr;

	delete Global::window;
	Global::window = nullptr;

	delete Global::deltaTime;
	Global::deltaTime = nullptr;

	exit(EXIT_SUCCESS);

}
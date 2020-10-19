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

int main(void) {

	Logger::init(WINDOW_TITLE, VERSION, true);

	//runDebugTools();

	if (!System::initOpenGL()) { return -1; }

	Global::window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 0, NULL);

	if (!Global::window->successfulCreation()) {

		Logger::getInstance()->errorLog("Failed to create window");

		return -1;

	}

	Global::applicationRunning = true;

	Global::window->setVsync(VSYNC);
	Global::window->setFpsLimit(MAX_FPS);
	Global::window->setDisplayFps(DISPLAY_FPS);

	Global::deltaTime = new Timer();

	Game* game = new Game();

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
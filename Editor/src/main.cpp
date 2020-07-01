#define GLFW_INCLUDE_NONE 1
#define GLFW_DLL 1
//#define GL_GLEXT_PROTOTYPES

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utilities/logger.h"
#include "Modules BackEnd/window.h"

#include "defaultSettings.h"
#include "global.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static void error_callback(int error, const char* description) {
	Logger::getInstance()->customLog("GLFW ERROR", description);

}

int main(void) {

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
	Global::wnd = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 0, NULL);

	if (!Global::wnd->successfulCreation()) {

		Logger::getInstance()->errorLog("glfwCreateWindow Error");

		glfwTerminate();

		return -1;

	}

	glfwMakeContextCurrent(Global::wnd->getWindow());

	Global::wnd->setVsync(VSYNC);
	Global::wnd->setFpsLimit(MAX_FPS);
	Global::wnd->setDisplayFps(DISPLAY_FPS);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::getInstance()->errorLog("Failed to initialize OpenGL context");
		return -1;
	}

	Logger::getInstance()->infoLog((char*)glGetString(GL_VERSION));
	Logger::getInstance()->infoLog(glfwGetVersionString());

	if (!GLAD_GL_VERSION_3_2) {

		Logger::getInstance()->errorLog("Your device must support OpenGL 3.2+");

		delete Global::wnd;
		Global::wnd = nullptr;

		glfwTerminate();

		return -1;

	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(Global::wnd->getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	//Window loop
	while (!glfwWindowShouldClose(Global::wnd->getWindow())) {

		Global::wnd->update();

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render your GUI
		ImGui::Begin("Demo window");
		ImGui::Button("Hello!");
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Swap front and back buffer
		glfwSwapBuffers(Global::wnd->getWindow());

		//Get window and input events
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	delete Global::wnd;
	Global::wnd = nullptr;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	exit(EXIT_SUCCESS);

}
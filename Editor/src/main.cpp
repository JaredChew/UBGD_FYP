#define GLFW_INCLUDE_NONE 1
#define GLFW_DLL 1
//#define GL_GLEXT_PROTOTYPES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <list>
#include <algorithm>
#include <vector>
#include <iterator>

#include "Utilities/logger.h"
#include "Modules BackEnd/window.h"
#include "Manipulators/shader.h"
#include "Manipulators/geometry.h"
#include "Compound/mesh.h"
#include "Compound/texture.h"
#include "Modules BackEnd/camera.h"
#include "Data Structure/linkedList.hpp"
#include "Specification/entity.h"
#include "Compound/transform.h"
#include "Manipulators/system.h"

#include "Compound/VertexArrayObject.h"

#include "defaultSettings.h"
#include "global.h"
#include "editor.h"

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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

	GLFWimage icon;
	System::loadImageToGLFWimage("icon/icon.png", icon);
	glfwSetWindowIcon(Global::wnd->getWindow(), 1, &icon);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	//(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(Global::wnd->getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");
	
	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	Editor::initEditor();
	

	//Window loop
	while (!glfwWindowShouldClose(Global::wnd->getWindow())) {
		
		//Global::wnd->update();

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::DockSpace();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit", "Alt+F4")) break;
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("TODO")) {
					//do something
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		bool show = true;
		//ImGui::ShowDemoWindow(&show);
		
		// render your GUI
		Editor::showEditor_Hierarchy();
		Editor::showEditor_Property();
		Editor::showEditor_AssetTracker();
		Editor::showEditor_WorldEditor();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		int display_w, display_h;
		glfwGetFramebufferSize(Global::wnd->getWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		//Swap front and back buffer
		glfwSwapBuffers(Global::wnd->getWindow());

		//Get window and input events
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	delete Global::wnd;
	Global::wnd = nullptr;

	Editor::terminateEditor();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	exit(EXIT_SUCCESS);

}
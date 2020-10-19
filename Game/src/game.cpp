#include "game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "defaultSettings.h"
#include "global.h"

#include "Specification/session.h"

#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"
#include "Modules BackEnd/mouse.h"

<<<<<<< HEAD
#include "Session/steeringBehaviour.h"
#include "Session/Testing_Scene.h"
=======
#include "Manipulators/renderer.h"
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487

#include "Compound/transform.h"

<<<<<<< HEAD
	//Init Opengl state
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	//glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do
=======
#include "Session/demo.h"
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487

Game::Game() {

	keyboard = new Keyboard(Global::window);
	mouse = new Mouse(Global::window);

<<<<<<< HEAD
	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(2.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(10.0f);

=======
	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487

	camera->setProjectionPerspective(glm::radians(FOV), Global::window->getWindowRatio(), 0.3f, 1000.0f);
	//camera->setProjectionOrthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 30.0f);

<<<<<<< HEAD
	camera = new Camera(wnd, kbd, mse, 3.0f, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	float w = 0.0f, h = 0.0f;
	if (wnd->getHeight() < wnd->getWidth())
	{
		w = 0.1f * FOV;
		h = 0.1f * static_cast<float>(wnd->getHeight()) / static_cast<float>(wnd->getWidth()) * FOV;
	}
	else if (wnd->getHeight() > wnd->getWidth())
	{
		w = 0.1f * static_cast<float>(wnd->getWidth()) / static_cast<float>(wnd->getHeight()) * FOV;
		h = 0.1f * FOV;
	}
	else
	{
		w = 0.1f * FOV;
		h = 0.1f * FOV;
	}



	//camera->projectionMatrix = glm::perspective<float>(glm::radians(FOV), wnd->getWindowRatio(), 0.5f, 1000.0f);
	camera->projectionMatrix = glm::ortho<float>(-w, w, -h, h, 0.5f, 300.0f);

	session = new Testing_Scene(wnd, kbd, mse, camera);
	//session = new SteeringBehaviour_Demo(wnd, kbd, mse, camera);
=======
	Renderer::start(WINDOW_WIDTH, WINDOW_HEIGHT);
	Renderer::getInstance()->useWindow(Global::window->getWindow());
	Renderer::getInstance()->useCamera(camera);

	session = new Demo();
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487

}

Game::~Game() {

	delete session;
	session = nullptr;

	delete camera;
	camera = nullptr;

	delete mouse;
	mouse = nullptr;

	delete keyboard;
	keyboard = nullptr;

}

void Game::freeCameraControl() {

	if (!keyboard->isPressed('Z')) { return; }

	//move
	if (mouse->isPressed(MOUSE_BUTTON_MIDDLE)) {

		camera->transform->translate(glm::vec3(mouse->getPositionOffset().x * 0.01f, -mouse->getPositionOffset().y * 0.01f, 0.0f));

	}

	//zoom
	if (mouse->getScrollDirection() != 0.0) { camera->transform->translate(glm::vec3(0.0f, 0.0f, mouse->getScrollDirection() * 2.5f)); }

	//rotate
	if (mouse->isPressed(MOUSE_BUTTON_RIGHT)) {

		camera->transform->rotate(glm::vec3(0.0f, mouse->getPositionOffset().x * 0.1f, 0.0f));
		camera->transform->rotateLocal(glm::vec3(mouse->getPositionOffset().y * -0.1f, 0.0f, 0.0f));

	}

}

void Game::initSessionState() {

	Session *newSession = session->getNextSession();

	delete session;
	session = nullptr;

	session = newSession;

}

void Game::gameLoop() {

	mouse->preUpdate();

	if (session == nullptr) { return; }

	freeCameraControl();

	session->preUpdate();
	session->update();
	session->postUpdate();
	session->render();

	mouse->postUpdate();
	keyboard->postUpdate();

	if (session->getNextSession() != nullptr) { initSessionState(); }

	if (Global::window->isDestroyed()) { Global::applicationRunning = false; }

}
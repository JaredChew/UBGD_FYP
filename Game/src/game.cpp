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

#include "Manipulators/renderer.h"

#include "Compound/transform.h"

#include "Session/demo.h"

Game::Game() {

	keyboard = new Keyboard(Global::window);
	mouse = new Mouse(Global::window);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	camera->setProjectionPerspective(glm::radians(FOV), Global::window->getWindowRatio(), 0.3f, 1000.0f);
	//camera->setProjectionOrthographic(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_HEIGHT, 0.5f, 300.0f);


	Renderer::start(WINDOW_WIDTH, WINDOW_HEIGHT);
	Renderer::getInstance()->useWindow(Global::window->getWindow());
	Renderer::getInstance()->useCamera(camera);

	session = new Demo();

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
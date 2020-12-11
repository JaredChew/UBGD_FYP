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

#include "Session/Testing_Scene.h"

#include "Manipulators/renderer.h"

#include "Compound/transform.h"

#include "Session/demo.h"

Game::Game() {

	keyboard = new Keyboard(Global::window);
	mouse = new Mouse(Global::window);

	camera = new Camera(glm::vec3(0.0f, 0.0f,-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	float w = 0.0f, h = 0.0f;
	float winH = static_cast<float>(Global::window->getHeight()), winW = static_cast<float>(Global::window->getWidth());
	if (winH < winW)
	{
		w = 0.1f * FOV;
		h = 0.1f * winH / winW * FOV;
	}
	else if (winH > winW)
	{
		w = 0.1f * winW / winH * FOV;
		h = 0.1f * FOV;
	}
	else
	{
		w = 0.1f * FOV;
		h = 0.1f * FOV;
	}

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(2.5f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	//glPointSize(10.0f);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	//camera->setProjectionPerspective(glm::radians(FOV), Global::window->getWindowRatio(), 0.3f, 300.0f);
	camera->setProjectionOrthographic(-w, w, -h, h, 0.1f, 3000.0f);


	Renderer::start(WINDOW_WIDTH, WINDOW_HEIGHT);
	Renderer::getInstance()->useWindow(Global::window->getWindow());
	Renderer::getInstance()->useCamera(camera);
	
	

	//session = new Testing_Scene();
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

	// quite testing

	
	float temp = static_cast<float>(Global::deltaTime->getDeltaTime() * 0.00000005);
	//camera->transform->setRotation(glm::vec3(0.0f, temp, 0.0f));
	if (glfwGetKey(Global::window->getWindow(), GLFW_KEY_Z) == GLFW_PRESS) {

		glm::vec3 newRot(0.0f, temp, 0.0f);
		camera->transform->setRotationLocal(camera->transform->getRotationLocal() + newRot);
	}
	if (glfwGetKey(Global::window->getWindow(), GLFW_KEY_C) == GLFW_PRESS) {

		glm::vec3 newRot(0.0f, -temp, 0.0f);
		camera->transform->setRotationLocal(camera->transform->getRotationLocal() + newRot);
	}
	if (glfwGetKey(Global::window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {

		glm::vec3 newRot(temp, 0.0f, 0.0f);
		camera->transform->setRotationLocal(camera->transform->getRotationLocal() + newRot);
	}
	if (glfwGetKey(Global::window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {

		glm::vec3 newRot(-temp, 0.0f, 0.0f);
		camera->transform->setRotationLocal(camera->transform->getRotationLocal() + newRot);
	}
	
	
	

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

	float w = 0.0f, h = 0.0f;
	float winH = static_cast<float>(Global::window->getHeight()), winW = static_cast<float>(Global::window->getWidth());
	if (winH < winW)
	{
		w = 0.1f * FOV;
		h = 0.1f * winH / winW * FOV;
	}
	else if (winH > winW)
	{
		w = 0.1f * winW / winH * FOV;
		h = 0.1f * FOV;
	}
	else
	{
		w = 0.1f * FOV;
		h = 0.1f * FOV;
	}

	camera->setProjectionOrthographic(-w, w, -h, h, 0.1f, 3000.0f);

	mouse->postUpdate();
	keyboard->postUpdate();

	if (session->getNextSession() != nullptr) { initSessionState(); }

	if (Global::window->isDestroyed()) { Global::applicationRunning = false; }

}
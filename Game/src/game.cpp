#include "game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "defaultSettings.h"

#include "Specification/session.h"

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"
#include "Modules BackEnd/mouse.h"

#include "Session/steeringBehaviour.h"
#include "Session/Testing_Scene.h"

Game::Game(Window *const wnd) : wnd(wnd) {

	//Init Opengl state
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	//glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(2.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(10.0f);


	kbd = new Keyboard(wnd);
	mse = new Mouse(wnd);

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

}

Game::~Game() {

	delete session;
	session = nullptr;

	delete camera;
	camera = nullptr;

	delete mse;
	mse = nullptr;

	delete kbd;
	kbd = nullptr;

}

void Game::initSessionState() {

	Session *newSession = session->getNextSession();

	delete session;
	session = nullptr;

	session = newSession;

}

void Game::gameLoop() {

	camera->update();

	mse->preUpdate();

	if (session == nullptr) { return; }

	session->preUpdate();
	session->update();
	session->postUpdate();
	session->render();

	mse->postUpdate();
	kbd->postUpdate();

	if (session->getNextSession() != nullptr) { initSessionState(); }

}
#include "Testing_Scene.h"

#include <iostream>

#include "Manipulators/openGL.h"

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/mouse.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"

#include "Utilities/random.h"

#include "Compound/texture.h"
#include "Compound/transform.h"
#include "Modules FrontEnd/sprite.h"

Testing_Scene::Testing_Scene(Window* const wnd, Keyboard* const kbd, Mouse* const mse, Camera* const camera) : wnd(wnd), kbd(kbd), mse(mse), camera(camera) {
	
	texture = new Texture("../Media/None.png"); //TreasureNormal.png");
	tranform = new Transform();
	//sprite = new Sprite(wnd,camera,);

	OpenGL::initTexture(screenTexture, 1, wnd->getWidth(), wnd->getHeight());
	OpenGL::initDepthBufferTexture(depthBuffer, wnd->getWidth(), wnd->getHeight());

	glGenFramebuffers(1, &frameBuffer);

}

Testing_Scene::~Testing_Scene() {

	delete texture;
	texture = nullptr;

	delete tranform;
	tranform = nullptr;

	glUseProgram(0);

}

void Testing_Scene::update() {


	//printf("%f\n", camera->getPosition().z);

	//tranform->setDimensionLocal(glm::vec3(1.0f, 1.0f, 1.0f));
	tranform->setDimension(glm::vec3(4.0f));

}

void Testing_Scene::render() {

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

		Sprite2::renderLighting(camera, texture, tranform);

	}

	renderToScreen(screenTexture, wnd->getWidth(), wnd->getHeight());

}
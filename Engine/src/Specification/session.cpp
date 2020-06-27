#include "Session.h"

Session::Session() {

	nextSession = nullptr;

	glGenFramebuffers(1, &frameBuffer);

}

Session::~Session() {

	delete nextSession;
	nextSession = nullptr;

}

void Session::preUpdate() {

	glBindTexture(GL_TEXTURE_2D, 0);

}

void Session::postUpdate() { }

void Session::render() { }

void Session::setNextSession(Session *nextSession) {
	this->nextSession = nextSession;
}

void Session::renderToScreen(const GLuint &texture, const int &resolutionWidth, const int &resolutionHeight) {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, resolutionWidth, resolutionHeight);

		Shader::defaultDraw(glm::mat4(1.0f));
		Geometry::drawSquare(texture);

	}

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

Session *Session::getNextSession() {

	Session *nextSession = this->nextSession;

	this->nextSession = nullptr;

	return nextSession;

}
#include "Session.h"

#include "../Manipulators/shader.h"
#include "../Manipulators/geometry.h"

Session::Session() {

	nextSession = nullptr;

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

Session *const Session::getNextSession() {

	Session *nextSession = this->nextSession;

	this->nextSession = nullptr;

	return nextSession;

}
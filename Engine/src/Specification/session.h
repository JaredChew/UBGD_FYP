#pragma once

#include "../Manipulators/openGL.h"
#include "../Manipulators/shader.h"
#include "../Manipulators/geometry.h"

class Session {

private:

	Session *nextSession;

	GLuint frameBuffer;

protected:

	void setNextSession(Session *nextSession);

	void renderToScreen(const GLuint &texture, const int &resolutionWidth, const int &resolutionHeight);

public:

	Session();

	Session *getNextSession();

	virtual ~Session();

	virtual void preUpdate();
	virtual void update() = 0;
	virtual void postUpdate();

	virtual void render();

};
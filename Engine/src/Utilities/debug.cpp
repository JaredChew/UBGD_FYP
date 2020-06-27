#include "debug.h"

void Debug::clearError() {

	if (!ENABLE_DEBUG) { return; }

	while (glGetError() != GL_NO_ERROR);

}

bool Debug::checkError(const char *function, const char *file, int line) {

	if (!ENABLE_DEBUG) { return false; }

	while (GLenum error = glGetError()) {

		std::stringstream errMsg;

		errMsg << "Error " << error << " at line " << line << " function " << function << " in " << file;

		Logger::getInstance()->customLog("OPENGL ERROR", errMsg.str());

		errMsg.clear();

		return true;

	}

	return false;

}
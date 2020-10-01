#include "debug.h"

#include "logger.h"

#include <glfw/glfw3.h>
#include <sstream>

void Debug::clearError() {

	if (!ENABLE_DEBUG) { return; }

	while (glGetError() != GL_NO_ERROR);

}

bool Debug::checkError(const char *function, const char *file, const int& line) {

	if (!ENABLE_DEBUG) { return false; }

	while (GLenum error = glGetError()) {

		Logger::getInstance()->customLog("OPENGL ERROR", "Error %s at function %s line %d in %s", error, function, line, file);

		return true;

	}

	return false;

}
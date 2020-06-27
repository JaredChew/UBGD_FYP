#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "logger.h"

#define ENABLE_DEBUG false

#ifdef _DEBUG

#undef  ENABLE_DEBUG
#define ENABLE_DEBUG true

#endif //_DEBUG

#if ENABLE_DEBUG

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define debug(glFunction) Debug::clearError(); glFunction; if(Debug::checkError(#glFunction, __FILENAME__, __LINE__)) __debugbreak();

#else // ENABLE_DEBUG

#define debugError(glFunction) glFunction

#endif // ENABLE_DEBUG

namespace Debug {

	void clearError();

	bool checkError(const char *function, const char *file, int line);

}
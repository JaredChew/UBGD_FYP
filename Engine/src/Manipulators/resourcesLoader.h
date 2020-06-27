#pragma once

#include <GLFW/glfw3.h>

#include "bitmap.h"

namespace Utilities { namespace ResourcesLoader {

	void loadTexture(const char* path, GLuint& textureID);

} }
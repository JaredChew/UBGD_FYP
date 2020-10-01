#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Specification/entity.h"

class Sprite;
class Window;
class Camera;

class Rock : public Entity {

public:

	Sprite* sprite;

	//float avoidanceRadius;

public:

	Rock(Window* const wnd, Camera* const camera, GLuint* const targetRender);
	~Rock();

	void render();

};
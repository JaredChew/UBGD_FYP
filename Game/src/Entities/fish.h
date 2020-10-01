#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Modules FrontEnd/boidEntity.h"

class Sprite;
class Window;
class Camera;

class Fish_AI : public BoidEntity {

public:

	Sprite* sprite;

public:

	Fish_AI(Window* const wnd, Camera* const camera, GLuint* const targetRender, const float& velocityLimit, const float& accelerationLimi);
	~Fish_AI();

	Transform& const getTransform();

	void render();

};
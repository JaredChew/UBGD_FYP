#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Specification/entity.h"

class Sprite;
class Keyboard;
class Window;
class Camera;

class Bait : public Entity {

private:

	Keyboard* const kbd;

public:

	Sprite* sprite;

	float movementSpeed;

public:

	Bait(Window* const wnd, Keyboard* const kbd, Camera* const camera, GLuint* const targetRender, const float& movementSpeed);

	virtual ~Bait();

	void controls(const float& deltaTime);
	void update(const float& deltaTime);
	void render();

};
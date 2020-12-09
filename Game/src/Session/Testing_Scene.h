#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Specification/session.h"

class Window;
class Keyboard;
class Mouse;
class Camera;
class Texture;
class Sprite;
class Transform;

class Testing_Scene : public Session
{
private:

	Window* const wnd;
	Keyboard* const kbd;
	Mouse* const mse;
	Camera* const camera;

private:

	GLuint frameBuffer;

	Texture* texture;
	Transform* tranform;
	Sprite* sprite;

	GLuint screenTexture;
	GLuint depthBuffer;

public:

	Testing_Scene(Window* const wnd, Keyboard* const kbd, Mouse* const mse, Camera* const camera);
	~Testing_Scene();

	// Inherited via Session
	void update() override;
	void render();
};

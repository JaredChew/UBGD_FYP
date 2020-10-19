#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Specification/session.h"

class Texture;
class Mesh;
class Transform;

class Demo : public Session {

private:

	Texture* texture;
	Mesh* mesh;
	Transform* transform;

private:

public:
	Demo();
	~Demo();

	void update() override;
	void render();

};
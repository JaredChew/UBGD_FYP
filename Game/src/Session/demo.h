#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Specification/session.h"

class Text;

struct GameObject;

struct LightingContainer;

class Demo : public Session {

private:

	std::vector<GameObject*> gameObjects;
	LightingContainer* lightingContainer;

	Text* text;

private:

public:
	Demo();
	~Demo();

	void update() override;
	void render();

};
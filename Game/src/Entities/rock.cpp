#include "rock.h"

#include <GLFW/glfw3.h>

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/camera.h"

#include "Modules FrontEnd/sprite.h"

#include "Compound/transform.h"

#include "Utilities/random.h"

#include "Compound/texture.h"

Rock::Rock(Window* const wnd, Camera* const camera, GLuint* const targetRender) {

	Texture *tex = new Texture("../Media/rock.bmp");

	sprite = new Sprite(wnd, camera, targetRender, tex);

	//transform->setDimensionLocal(glm::vec3(1.3f, 2.2f, 1.0f));

	transform->setPosition(glm::vec3(
		Utilities::Random::randBetweenFloat(-30.0f, 30.0f),
		Utilities::Random::randBetweenFloat(-30.0f, 30.0f),
		0.0f
	));

	transform->setRotationLocal(glm::vec3(
		0.0f,
		0.0f,
		Utilities::Random::randBetweenFloat(-50.0f, 50.0f)
	));

	transform->setDimensionLocal(glm::vec3(
		Utilities::Random::randBetweenFloat(1.0f, 1.5f),
		Utilities::Random::randBetweenFloat(1.0f, 1.5f),
		0.0f
	));

	//avoidanceRadius = glm::length(transform.getDimensionLocal()) * 0.01f;

}

Rock::~Rock() {

	delete sprite;
	sprite = nullptr;

}

void Rock::render() {

	sprite->renderSprite(*transform);

}

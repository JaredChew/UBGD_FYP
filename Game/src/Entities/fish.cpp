#include "fish.h"

#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/window.h"

#include "Modules FrontEnd/sprite.h"

#include "Compound/texture.h"

Fish_AI::Fish_AI(Window* const wnd, Camera* const camera, GLuint* const targetRender, const float& velocityLimit, const float& accelerationLimi) : BoidEntity() {

	Texture* tex = new Texture("../Media/fish.bmp");

	sprite = new Sprite(wnd, camera, targetRender, tex);

	setVelocityLimit(velocityLimit);
	setAccelerationLimit(accelerationLimi);

	//transform.setDimensionLocal(glm::vec3(1.3f, 2.2f, 1.0f));

}

Fish_AI::~Fish_AI() {

	delete sprite;
	sprite = nullptr;

}

Transform& const Fish_AI::getTransform() {
	return *transform;
}

void Fish_AI::render() {

	sprite->renderSprite(*transform);

}

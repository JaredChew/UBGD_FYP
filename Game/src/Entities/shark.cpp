#include "shark.h"

#include <glm/gtc/constants.hpp>

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"

#include "Modules FrontEnd/sprite.h"

#include "Compound/transform.h"

#include "Utilities/random.h"

#include "Compound/texture.h"

Shark::Shark(Window* const wnd, Keyboard* const kbd, Camera* const camera, GLuint* const targetRender, const float& movementSpeed) : Entity(), kbd(kbd) {

	Texture* tex = new Texture("../Media/shark.bmp");

	sprite = new Sprite(wnd, camera, targetRender, tex);

	this->movementSpeed = movementSpeed;

	transform->setDimensionLocal(glm::vec3(1.5f, 2.0f, 1.0f));

	transform->setPosition(
		glm::vec3(Utilities::Random::randBetweenFloat(-10.0f, 10.0f),
			Utilities::Random::randBetweenFloat(-10.0f, 10.0f),
			0.0f)
	);

}

Shark::~Shark() {

	delete sprite;
	sprite = nullptr;

}

void Shark::controls(const float& deltaTime) {

	float movementSpeed = this->movementSpeed * deltaTime;

	if (kbd->isPressed('I')) { transform->translate(glm::vec3(0.0f, movementSpeed * 2.0f, 0.0f)); }
	if (kbd->isPressed('J')) { transform->translate(glm::vec3(-movementSpeed, 0.0f, 0.0f)); }
	if (kbd->isPressed('K')) { transform->translate(glm::vec3(0.0f, -movementSpeed * 2.0f, 0.0f)); }
	if (kbd->isPressed('L')) { transform->translate(glm::vec3(movementSpeed, 0.0f, 0.0f)); }

}

void Shark::update(const float& deltaTime) {

	controls(deltaTime);

	float rotate = atan2(transform->getPosition().y, transform->getPosition().x) * (float)(180.0f / glm::pi<float>());

	transform->setRotationLocal(glm::vec3(0.0f, 0.0f, rotate));

}

void Shark::render() {

	sprite->renderSprite(*transform);

}

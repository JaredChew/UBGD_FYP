#include "bait.h"

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"

#include "Modules FrontEnd/sprite.h"

#include "Compound/transform.h"

#include "Utilities/random.h"

#include "Compound/texture.h"

Bait::Bait(Window* const wnd, Keyboard* const kbd, Camera* const camera, GLuint* const targetRender, const float& movementSpeed) : Entity(), kbd(kbd) {

	Texture* tex = new Texture("../Media/particle.bmp");

	sprite = new Sprite(wnd, camera, targetRender, tex);

	sprite->setBlendColour(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	sprite->setBlendType(Sprite::BlendType::BLEND_MULTIPLY, false);

	this->movementSpeed = movementSpeed;

	transform->setPosition(
		glm::vec3(Utilities::Random::randBetweenFloat(-10.0f, 10.0f),
			Utilities::Random::randBetweenFloat(-10.0f, 10.0f),
			0.0f)
	);

}

Bait::~Bait() {

	delete sprite;
	sprite = nullptr;

}

void Bait::controls(const float& deltaTime) {

	float movementSpeed = this->movementSpeed * deltaTime;

	if (kbd->isPressed('W')) { transform->translate(glm::vec3(0.0f, movementSpeed * 2.0f, 0.0f)); }
	if (kbd->isPressed('A')) { transform->translate(glm::vec3(-movementSpeed, 0.0f, 0.0f)); }
	if (kbd->isPressed('S')) { transform->translate(glm::vec3(0.0f, -movementSpeed * 2.0f, 0.0f)); }
	if (kbd->isPressed('D')) { transform->translate(glm::vec3(movementSpeed, 0.0f, 0.0f)); }

}

void Bait::update(const float& deltaTime) {

	controls(deltaTime);

}

void Bait::render() {

	sprite->renderSprite(*transform);

}

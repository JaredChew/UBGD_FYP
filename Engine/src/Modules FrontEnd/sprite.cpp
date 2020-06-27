#include "sprite.h"

Sprite::Sprite(Window *const wnd, Camera *const camera, const char *directory, GLuint *const targetRender, const int &spriteWidth, const int &spriteHeight, const int &sheetRow, const int &sheetCol, const int &animationFrameRate) : wnd(wnd), camera(camera), targetRender(targetRender) {

	glGenFramebuffers(1, &frameBuffer);

	CBitmap bitmap(directory);

	textureWidth = bitmap.GetWidth();
	textureHeight = bitmap.GetHeight();
	
	OpenGL::initTexture(texture, 1, textureWidth, textureHeight);
	OpenGL::initTexture(textureProcessed, 1, textureWidth, textureHeight);
	OpenGL::initTexture(textureToRender, 1, wnd->getWidth(), wnd->getHeight());

	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;

	this->sheetRow = sheetRow;
	this->sheetCol = sheetCol;

	totalAnimationFrames = 0;
	this->animationFrameRate = animationFrameRate;

	isAnimatedSprite = false;

	if (animationFrameRate) {
		totalAnimationFrames = sheetRow + sheetCol;
		isAnimatedSprite = true;
	}

	blendType = BlendType::BLEND_ADDITIVE;

	animationRow = 0;
	animationCol = 0;

	animationFrame = 0;
	totalFramesPassed = 0;

	isAnimationOneShot = false;
	isBillboard = false;
	isAlphaBlend = false;

	colourBlend = glm::vec4(0.0f);

	deltaTime = std::chrono::nanoseconds(0);
	deltaTime_s = std::chrono::duration<double>(0.0);

	tick = std::chrono::high_resolution_clock::now();

	OpenGL::loadTexture(bitmap, texture);

	GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
	GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/default.frag");

	if (!OpenGL::initProgramObject_Shader(animationShaderProgram, fragmentShader, vertexShader)) {
		Logger::getInstance()->warningLog("Failed to init animation shader program");
	}

}

Sprite::~Sprite() {

	glDeleteTextures(1, &texture);

	glDeleteProgram(animationShaderProgram);

}

void Sprite::blendColourAndTexture() {

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureProcessed, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, textureWidth, textureHeight);

		float alphaColour = isAlphaBlend ? colourBlend.w : ((int)blendType ? 1.0f : 0.0f);

		Shader::blendColour(glm::mat4(1.0f), (int)blendType, colourBlend.x, colourBlend.y, colourBlend.z, alphaColour);

		Geometry::drawSquare(texture);

	}

}

glm::mat4 Sprite::transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension) {

	return glm::translate(glm::mat4(1.0f), glm::vec3(position)) *

		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *

		glm::scale(glm::mat4(1.0f), glm::vec3(dimension.x, dimension.y, 0.0f));

}

glm::mat4 Sprite::produceModelViewMatrix(const glm::mat4 &modelMatrix) {

	glm::mat4 modelViewMatrix = camera->getViewMatrix() * modelMatrix;

	if (isBillboard) {
		
		// 1st colunm
		glm::value_ptr(modelViewMatrix)[0] = 1.0;
		glm::value_ptr(modelViewMatrix)[1] = 0.0;
		glm::value_ptr(modelViewMatrix)[2] = 0.0;

		// 2nd colunm
		glm::value_ptr(modelViewMatrix)[4] = 0.0;
		glm::value_ptr(modelViewMatrix)[5] = 1.0;
		glm::value_ptr(modelViewMatrix)[6] = 0.0;

		// 3rd colunm
		glm::value_ptr(modelViewMatrix)[8] = 0.0;
		glm::value_ptr(modelViewMatrix)[9] = 0.0;
		glm::value_ptr(modelViewMatrix)[10] = 1.0;
		
	}

	return modelViewMatrix;

}

void Sprite::setIsAnimationOneShot(const bool &isAnimationOneShot) {

	this->isAnimationOneShot = isAnimationOneShot;

	animationRow = 0;
	animationCol = 0;

	animationFrame = 0;

}

void Sprite::setIsBillboard(const bool &isBillboard) {
	this->isBillboard = isBillboard;
}

void Sprite::setBlendColour(const glm::vec4 &colourBlend) {
	this->colourBlend = colourBlend;
}

void Sprite::setBlendType(const BlendType &blendType, const bool &isAlphaBlend) {

	this->blendType = blendType;
	this->isAlphaBlend = isAlphaBlend;

}

void Sprite::renderSprite(const glm::mat4 &mvpMatrix) {

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	blendColourAndTexture();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *targetRender, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

		glBindTexture(GL_TEXTURE_2D, textureProcessed);

		Shader::defaultDraw(mvpMatrix);
		Geometry::drawSquare(textureProcessed);

	}

}

void Sprite::renderSprite(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension) {

	glm::mat4 modelMatrix = transform(position, rotation, dimension);

	glm::mat4 modelViewMatrix = produceModelViewMatrix(modelMatrix);

	renderSprite(camera->projectionMatrix * modelViewMatrix);

}

void Sprite::renderSprite(Transform &transform) {

	glm::mat4 modelViewMatrix = produceModelViewMatrix(transform.getModelMatrix());

	renderSprite(camera->projectionMatrix * modelViewMatrix);

}

void Sprite::renderSprite(const glm::mat4 &mvpMatrix, const int &frameRow, const int &frameCol) {

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	blendColourAndTexture();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureToRender, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

		Shader::cutFrameCell(mvpMatrix, textureWidth, textureHeight, frameRow, frameCol);
		Geometry::drawSquare(textureProcessed);

	}

}

void Sprite::renderSprite(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension, const int &frameRow, const int &frameCol) {

	glm::mat4 modelMatrix = transform(position, rotation, dimension);

	glm::mat4 modelViewMatrix = produceModelViewMatrix(modelMatrix);

	renderSprite(camera->projectionMatrix * modelViewMatrix);

}

void Sprite::renderSprite(Transform &transform, const int &frameRow, const int &frameCol) {

	glm::mat4 modelViewMatrix = produceModelViewMatrix(transform.getModelMatrix());

	renderSprite(camera->projectionMatrix * modelViewMatrix, frameRow, frameCol);

}

void Sprite::renderAnimation(const glm::mat4 &mvpMatrix) {

	if (!isAnimatedSprite) { return; }

	if (isAnimationOneShot && animationFrame >= totalAnimationFrames) { return; }

	tock = std::chrono::high_resolution_clock::now();

	deltaTime += std::chrono::duration_cast<std::chrono::nanoseconds>(tock - tick);
	//deltaTime_s += tock - tick;

	if (totalFramesPassed >= animationFrameRate && deltaTime.count() < 1000000000) {

		renderSprite(mvpMatrix, animationRow, animationCol);

		++animationFrame;
		++animationRow;

		if (animationRow >= sheetRow) {
			++animationCol;
			animationRow = 0;
		}

		deltaTime = std::chrono::nanoseconds(0);

	}

	if (deltaTime.count() >= 1000000000) { deltaTime = std::chrono::nanoseconds(0); }

	tick = tock;

	if (!isAnimationOneShot && animationFrame >= totalAnimationFrames) { animationFrame = 0; }

	++totalFramesPassed;

}

void Sprite::renderAnimation(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension) {

	glm::mat4 modelMatrix = transform(position, rotation, dimension);

	renderAnimation(modelMatrix * camera->projectionMatrix * camera->getViewMatrix());

}

void Sprite::renderAnimation(Transform &transform) {

	renderAnimation(transform.getModelMatrix() * camera->projectionMatrix * camera->getViewMatrix());

}

void Sprite::setAnimationFrameRate(const int &animationFrameRate) {
	this->animationFrameRate = animationFrameRate;
}

int Sprite::getAnimationFrameRate() { return animationFrameRate; }

int Sprite::getAnimationFrame() { return animationFrame; }

bool Sprite::getIsAnimatedSprite() { return isAnimatedSprite; }

bool Sprite::getIsAnimationOneShot() {
	return isAnimationOneShot;
}

bool Sprite::getIsBillboard() {
	return isBillboard;
}

bool Sprite::getIsAlphaBlend() {
	return isAlphaBlend;
}

GLuint Sprite::getTexture() {
	return textureProcessed;
}

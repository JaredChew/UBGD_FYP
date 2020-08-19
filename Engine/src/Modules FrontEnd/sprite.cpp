#include "sprite.h"

//#include "bitmap.h"

#include "../Utilities/logger.h"
#include "../Utilities/timer.h"

#include "../Manipulators/openGL.h"
#include "../Manipulators/geometry.h"
#include "../Manipulators/shader.h"

#include "../Compound/transform.h"
#include "../Compound/texture.h"
#include "../Compound/animation2D.h"

#include "../Modules BackEnd/window.h"
#include "../Modules BackEnd/camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sprite::Sprite(Window* const wnd, Camera* const camera, GLuint* const targetRender, Texture* const texture, const int& spriteWidth, const int& spriteHeight, const int& sheetRow, const int& sheetCol, const int& animationFrameRate) : wnd(wnd), camera(camera), targetRender(targetRender), texture(texture) {

	glGenFramebuffers(1, &frameBuffer);

	//CBitmap bitmap(directory);

	//textureWidth = bitmap.GetWidth();
	//textureHeight = bitmap.GetHeight();

	//OpenGL::initTexture(texture, 1, textureWidth, textureHeight);
	OpenGL::initTexture(textureProcessed, 1, this->texture->getWidth(), this->texture->getHeight());
	OpenGL::initTexture(textureToRender, 1, wnd->getWidth(), wnd->getHeight());

	//this->spriteWidth = spriteWidth;
	//this->spriteHeight = spriteHeight;

	//this->sheetRow = sheetRow;
	//this->sheetCol = sheetCol;

	isAnimatedSprite = false;


	blendType = BlendType::BLEND_ADDITIVE;

	

	isAnimationOneShot = false;
	isBillboard = false;
	isAlphaBlend = false;

	colourBlend = glm::vec4(0.0f);

	timer = new Timer();

	//OpenGL::loadTexture(directory, texture);

	GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
	GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/default.frag");

	if (!OpenGL::initProgramObject_Shader(animationShaderProgram, fragmentShader, vertexShader)) {
		Logger::getInstance()->warningLog("Failed to init animation shader program");
	}

	Geometry::setSquare(animationShaderProgram, vertexArrayObjectID, Geometry::setVertexArrayObject);

}

Sprite::~Sprite() {

	glDeleteProgram(animationShaderProgram);

}

void Sprite::blendColourAndTexture() {

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_ALPHA);
	glEnable(GL_BLEND);

	switch (blendType)
	{
	case BlendType::BLEND_ADDITIVE:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		break;

	case BlendType::BLEND_MULTIPLY:
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBlendEquation(GL_FUNC_ADD);
		break;

	case BlendType::BLEND_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
		break;
	}
	/*
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureProcessed, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, textureWidth, textureHeight);

		float alphaColour = isAlphaBlend ? colourBlend.w : ((int)blendType ? 1.0f : 0.0f);

		Shader::blendColour(glm::mat4(1.0f), (int)blendType, colourBlend.x, colourBlend.y, colourBlend.z, alphaColour);

		Geometry::drawSquare(texture->getGtextureID());

	}
	*/
}

glm::mat4 Sprite::transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension) {

	return glm::translate(glm::mat4(1.0f), glm::vec3(position)) *

		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *

		glm::scale(glm::mat4(1.0f), glm::vec3(dimension.x, dimension.y, 0.0f));

}

glm::mat4 Sprite::produceModelViewMatrix(const glm::mat4& modelMatrix) {

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



void Sprite::setIsBillboard(const bool& isBillboard) {
	this->isBillboard = isBillboard;
}

void Sprite::setTexture(Texture* texture)
{
	this->texture = texture;
}

void Sprite::setBlendColour(const glm::vec4& colourBlend) {
	this->colourBlend = colourBlend;
}

void Sprite::setBlendType(const BlendType& blendType, const bool& isAlphaBlend) {

	this->blendType = blendType;
	this->isAlphaBlend = isAlphaBlend;

}

void Sprite::render(Transform& transform)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *targetRender, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

		glBindTexture(GL_TEXTURE_2D, textureProcessed);

		Shader::defaultDraw(transform.getModelMatrix());
		Geometry::drawSquare(textureProcessed);

	}

}

void Sprite::renderAnimation(Animation2D& animation, Transform& transform)
{
	glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

	blendColourAndTexture();

	glBindTexture(GL_TEXTURE_2D, texture->getGtextureID());

	Shader::animation2DDraw( transform.getModelMatrix(),
		animation.getAnimation2DInfo().rawAnimationRow, animation.getAnimation2DInfo().rawAnimationCol,
		animation.getAnimation2DInfo().eachNorRowSize, animation.getAnimation2DInfo().eachNorColSize,
		animation.getCurrentKeyFrame() );

	Geometry::drawVertexArrayObject(vertexArrayObjectID, Geometry::getSquareIndicesSize());

}

void Sprite::renderSprite(const glm::mat4& mvpMatrix) {

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

void Sprite::renderSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension) {

	glm::mat4 modelMatrix = transform(position, rotation, dimension);

	glm::mat4 modelViewMatrix = produceModelViewMatrix(modelMatrix);

	renderSprite(camera->projectionMatrix * modelViewMatrix);

}

void Sprite::renderSprite(Transform& transform) {

	glm::mat4 modelViewMatrix = produceModelViewMatrix(transform.getModelMatrix());

	renderSprite(camera->projectionMatrix * modelViewMatrix);

}

void Sprite::renderSprite(const glm::mat4& mvpMatrix, const int& frameRow, const int& frameCol) {

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	blendColourAndTexture();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureToRender, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

		Shader::cutFrameCell(mvpMatrix, textureWidth, textureHeight, frameRow, frameCol);
		Geometry::drawSquare(textureProcessed);

	}

}

void Sprite::renderSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension, const int& frameRow, const int& frameCol) {

	glm::mat4 modelMatrix = transform(position, rotation, dimension);

	glm::mat4 modelViewMatrix = produceModelViewMatrix(modelMatrix);

	renderSprite(camera->projectionMatrix * modelViewMatrix);

}

void Sprite::renderSprite(Transform& transform, const int& frameRow, const int& frameCol) {

	glm::mat4 modelViewMatrix = produceModelViewMatrix(transform.getModelMatrix());

	renderSprite(camera->projectionMatrix * modelViewMatrix, frameRow, frameCol);

}

void Sprite::renderAnimation(const glm::mat4& mvpMatrix) {

	if (!isAnimatedSprite) { return; }

	//if (isAnimationOneShot && animationFrame >= totalAnimationFrames) { return; }

	timer->recordTock();

	deltaTime += timer->getDeltaTime();
	/*
	if (totalFramesPassed >= animationFrameRate && deltaTime < 1000000000) {

		renderSprite(mvpMatrix, animationRow, animationCol);

		++animationFrame;
		++animationRow;

		if (animationRow >= sheetRow) {
			++animationCol;
			animationRow = 0;
		}

		deltaTime = 0;

	}
	
	if (deltaTime >= 1000000000) { deltaTime = 0; }

	timer->recordTick();

	if (!isAnimationOneShot && animationFrame >= totalAnimationFrames) { animationFrame = 0; }

	++totalFramesPassed;
	*/
}

void Sprite::renderAnimation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension) {

	glm::mat4 modelMatrix = transform(position, rotation, dimension);

	renderAnimation(modelMatrix * camera->projectionMatrix * camera->getViewMatrix());

}

void Sprite::renderAnimation(Transform& transform) {

	renderAnimation(transform.getModelMatrix() * camera->projectionMatrix * camera->getViewMatrix());

}



bool Sprite::getIsBillboard() {
	return isBillboard;
}

bool Sprite::getIsAlphaBlend() {
	return isAlphaBlend;
}

Texture* Sprite::getTexture()
{
	return texture;
}

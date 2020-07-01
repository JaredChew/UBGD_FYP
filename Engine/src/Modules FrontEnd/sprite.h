#pragma once

#include <glad/glad.h>

#include <chrono>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Transform;
class Window;
class Camera;
class Timer;

class Sprite {

private:

	Window *const wnd;
	Camera *const camera;

	GLuint *const targetRender;

public:

	enum class BlendType { BLEND_ADDITIVE, BLEND_MULTIPLY };

private:

	GLuint texture;
	GLuint textureProcessed;
	GLuint textureToRender;

	GLuint frameBuffer;

	GLuint animationShaderProgram;

	glm::vec4 colourBlend;

	BlendType blendType;

	int textureWidth;
	int textureHeight;

	int spriteWidth;
	int spriteHeight;

	int sheetRow;
	int sheetCol;

	int totalAnimationFrames;
	int animationFrameRate;

	int animationRow;
	int animationCol;

	int animationFrame;
	int totalFramesPassed;

	bool isAnimatedSprite;
	bool isAnimationOneShot;
	bool isBillboard;
	bool isAlphaBlend;

	Timer* timer;

private:

	void blendColourAndTexture();

	glm::mat4 transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension);
	glm::mat4 produceModelViewMatrix(const glm::mat4 &modelMatrix);

public:

	Sprite(Window *const wnd, Camera *const camera, const char *directory, GLuint *const targetRender, const int &spriteWidth = 0, const int &spriteHeight = 0, const int &sheetRow = 0, const int &sheetCol = 0, const int &animationFrameRate = 0);
	~Sprite();

	void setIsAnimationOneShot(const bool &isAnimationOneShot);
	void setIsBillboard(const bool &isBillboard);

	void setBlendColour(const glm::vec4 &colourBlend);
	void setBlendType(const BlendType &blendType, const bool &isAlphaBlend);

	//singular
	void renderSprite(const glm::mat4 &mvpMatrix = glm::mat4(1.0f));
	void renderSprite(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension);
	void renderSprite(Transform &transform);

	//sheet
	void renderSprite(const glm::mat4 &mvpMatrix, const int &frameRow, const int &frameCol);
	void renderSprite(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension, const int &frameRow, const int &frameCol);
	void renderSprite(Transform &transform, const int &frameRow, const int &frameCol);

	//animation
	void renderAnimation(const glm::mat4 &mvpMatrix = glm::mat4(1.0f));
	void renderAnimation(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec2 &dimension);
	void renderAnimation(Transform &transform);

	void setAnimationFrameRate(const int &animationFrameRate);

	int getAnimationFrameRate();
	int getAnimationFrame();

	bool getIsAnimatedSprite();
	bool getIsAnimationOneShot();
	bool getIsBillboard();
	bool getIsAlphaBlend();

	GLuint getTexture();

};
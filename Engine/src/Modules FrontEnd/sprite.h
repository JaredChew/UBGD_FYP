#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


class Window;
class Camera;
class Texture;
class Transform;
class Animation2D;
class Timer;

class Sprite {

private:

	Window* const wnd;
	Camera* const camera;

	GLuint* const targetRender;

	Texture* texture;

public:

	enum class BlendType { BLEND_ADDITIVE, BLEND_MULTIPLY, BLEND_ALPHA };

private:
	
	GLuint textureProcessed;
	GLuint textureToRender;
	GLuint vertexArrayObjectID;

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

	bool isAnimatedSprite;
	bool isAnimationOneShot;
	bool isBillboard;
	bool isAlphaBlend;

	unsigned long long int deltaTime;

	Timer* timer;

private:

	void blendColourAndTexture();

	glm::mat4 transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension);
	glm::mat4 produceModelViewMatrix(const glm::mat4& modelMatrix);

public:

	Sprite(Window* const wnd, Camera* const camera, GLuint* const targetRender, Texture* const texture, const int& spriteWidth = 0, const int& spriteHeight = 0, const int& sheetRow = 0, const int& sheetCol = 0, const int& animationFrameRate = 0);
	~Sprite();

	void setIsBillboard(const bool& isBillboard);

	void setTexture(Texture* texture);
	void setBlendColour(const glm::vec4& colourBlend);
	void setBlendType(const BlendType& blendType, const bool& isAlphaBlend);

	void render(Transform& transform);
	void renderAnimation(Animation2D& animation, Transform& transform);

	//singular
	void renderSprite(const glm::mat4& mvpMatrix = glm::mat4(1.0f));
	void renderSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension);
	void renderSprite(Transform& transform);

	//sheet
	void renderSprite(const glm::mat4& mvpMatrix, const int& frameRow, const int& frameCol);
	void renderSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension, const int& frameRow, const int& frameCol);
	void renderSprite(Transform& transform, const int& frameRow, const int& frameCol);

	//animation
	void renderAnimation(const glm::mat4& mvpMatrix = glm::mat4(1.0f));
	void renderAnimation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& dimension);
	void renderAnimation(Transform& transform);

	bool getIsBillboard();
	bool getIsAlphaBlend();

	Texture* getTexture();

};
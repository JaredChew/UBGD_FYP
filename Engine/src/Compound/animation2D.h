#pragma once

#include <glad/glad.h>
#include <vector>

class Timer;
class Sprite;
class Transform;
class Texture;

enum class Animation2DMode { OneShot = 0, Looping };

struct Animation2DSpriteSheet {

private:
	const int SECOND_TO_NANOSECOND = 100000000;

public:
	Texture* texture;
	GLuint rawTotalAnimationFrame, rawAnimationRow, rawAnimationCol;
	GLsizei eachNorRowSize, eachNorColSize;

	Animation2DSpriteSheet()
	{
		rawTotalAnimationFrame = rawAnimationRow = rawAnimationCol = 0;
		texture = nullptr;
		eachNorRowSize = eachNorColSize = 0;
	}
	Animation2DSpriteSheet(const GLuint& row, const GLuint& column, Texture* texture)
	{
		rawAnimationRow = ((row <= 0) ? 1 : row);
		rawAnimationCol = ((column <= 0) ? 1 : column);
		rawTotalAnimationFrame = rawAnimationRow * rawAnimationCol;
		this->texture = texture;
		
		eachNorRowSize = 1.0f / static_cast<float>(rawAnimationRow);
		eachNorColSize = 1.0f / static_cast<float>(rawAnimationCol);

	}
	~Animation2DSpriteSheet()
	{
		this->texture = nullptr;
	}

};

class Animation2D 
{
private:
	const int SECOND_TO_NANOSECOND = 100000000;

private:

	Animation2DMode animation2DMode;
	Animation2DSpriteSheet animation2DSpriteSheet; // All information from Animator2D class

	GLuint totalKeyFrames, keyFrameIndex; //, totalPassedFrames;

	std::vector<GLuint> keyFrames; // The Animation2D itself

	unsigned long long int totalAnimationFrameRate;
	unsigned long long int eachAnimationFrameRate;
	unsigned long long int targetAnimationFrameRate;
	unsigned long long int currentFrameRate;

	Timer* timer;


public:

	Animation2D();
	Animation2D(Timer* time, Texture* texture, const GLuint& row, const GLuint& column, const Animation2DMode& mode = Animation2DMode::OneShot);
	Animation2D(Timer* time, const Animation2DSpriteSheet& spriteSheet, const Animation2DMode& mode = Animation2DMode::OneShot);
	~Animation2D();


	void restartAnimation(void);
	void clearKeyFrame(void);

	const bool& addKeyFrame(const GLuint& whichRow, const GLuint& whichColumn);
	const bool& addKeyFrame(const GLuint& index);
	const bool& setKeyFrame(const GLuint& size, GLuint* indexs);
	const bool& setKeyFrameOrderDependSize(void);


	void setMode(const Animation2DMode& mode);
	void setAnimationFrameRate(const GLuint& frameRateInSecond); // One second have how many key frame
	void setAnimationFrameRate(const double& timeOfScenod); // One second have how many key frame


	const unsigned long long int& const getAnimationFrameRateInSecond(void) const;
	const GLuint& const getCurrentKeyFrame(void) const;
	const GLuint& const getCurrentKeyFrameIndex(void) const;
	const Animation2DSpriteSheet& const getAnimation2DSpriteSheet(void) const;
	const Animation2DMode& const getAnimation2DMode(void) const;

	void draw();
	void update();

};
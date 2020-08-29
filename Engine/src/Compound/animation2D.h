#pragma once

#include <glad/glad.h>
#include <vector>

class Timer;
class Sprite;
class Transform;
class Texture;

typedef unsigned long long int Nanosecond;
#define OneSecondToNanosecond 100000000

enum class Animation2DMode { OneShot = 0, Looping };

struct Animation2DSpriteSheet
{
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
		//eachRowSize = ((texture->getWidth() <= 0) ? 0 : (texture->getWidth() / rawAnimationRow));
		//eachColSize = ((texture->getHeight() <= 0) ? 0 : (texture->getHeight() / rawAnimationCol));
	}
	~Animation2DSpriteSheet()
	{
		this->texture = nullptr;
	}

};

class Animation2D 
{
private:

	Animation2DMode animation2DMode;

	// All information from Animator2D class
	Animation2DSpriteSheet animation2DSpriteSheet;

	// The Animation2D itself
	std::vector<GLuint> keyFrames;
	GLuint totalKeyFrames, keyFrameIndex; //, totalPassedFrames;

	Nanosecond totalAnimationFrameRate, eachAnimationFrameRate, targetAnimationFrameRate;
	Nanosecond currentFrameRate;

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


	const Nanosecond& const getAnimationFrameRateInSecond(void) const;
	const GLuint& const getCurrentKeyFrame(void) const;
	const GLuint& const getCurrentKeyFrameIndex(void) const;
	const Animation2DSpriteSheet& const getAnimation2DSpriteSheet(void) const;
	const Animation2DMode& const getAnimation2DMode(void) const;


	void update();

};
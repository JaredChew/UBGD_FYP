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

struct Animation2DInfo
{
public:
	Texture* texture;
	GLuint rawTotalAnimationFrame, rawAnimationRow, rawAnimationCol;
	GLsizei eachNorRowSize, eachNorColSize;

	Animation2DInfo()
	{
		rawTotalAnimationFrame = rawAnimationRow = rawAnimationCol = 0;
		texture = nullptr;
		eachNorRowSize = eachNorColSize = 0;
	}
	Animation2DInfo(const GLuint& row, const GLuint& column, Texture* texture)
	{
		rawAnimationRow = ((row <= 0) ? 1 : row);
		rawAnimationCol = ((column <= 0) ? 1 : column);
		rawTotalAnimationFrame = rawAnimationRow * rawAnimationCol;
		this->texture = texture;
		
		eachNorRowSize = 1.0f / rawAnimationRow;
		eachNorColSize = 1.0f / rawAnimationCol;
		//eachRowSize = ((texture->getWidth() <= 0) ? 0 : (texture->getWidth() / rawAnimationRow));
		//eachColSize = ((texture->getHeight() <= 0) ? 0 : (texture->getHeight() / rawAnimationCol));
	}
	~Animation2DInfo()
	{
		this->texture = nullptr;
	}

};

class Animation2D 
{
private:

	Animation2DMode animation2DMode;

	// All information from Animator2D class
	Animation2DInfo animation2DInfo;

	// The Animation2D itself
	std::vector<GLuint> keyFrames;
	GLuint totalKeyFrames, currentKeyFrame; //, totalPassedFrames;

	GLuint animationFrameRate;
	Nanosecond totalAnimationFrameRate, eachAnimationFrameRate, currentAnimationFrameRate;

	Nanosecond deltaTime;

	Timer* timer;


public:

	Animation2D();
	Animation2D(Timer* time, Texture* texture, const GLuint& row, const GLuint& column, const Animation2DMode& mode = Animation2DMode::OneShot);
	Animation2D(Timer* time, const Animation2DInfo& info, const Animation2DMode& mode = Animation2DMode::OneShot);
	~Animation2D();


	void clearKeyFrame(void);
	const bool& addKeyFrame(const GLuint& whichRow, const GLuint& whichColumn);
	const bool& addKeyFrame(const GLuint& index);


	void setMode(const Animation2DMode& mode);
	void setAnimationFrameRate(const GLuint& frameRate); // One second have how many key frame


	const GLuint& const getAnimationFrameRate(void) const;
	const GLuint& const getCurrentKeyFrame(void) const;
	const Animation2DInfo& const getAnimation2DInfo(void) const;
	const Animation2DMode& const getAnimation2DMode(void) const;


	void update();

};
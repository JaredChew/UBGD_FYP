#pragma once

#include <glad/glad.h>

#include <vector>

class Animator2D {

private:
	const int SECOND_TO_NANOSECOND = 100000000;

public:

	enum class AnimationMode { ONE_SHOT, LOOP };

private:

	AnimationMode mode;

	GLuint rawAnimationRow;
	GLuint rawAnimationCol;
	GLuint rawTotalAnimationFrame;

	GLsizei eachNorRowSize;
	GLsizei eachNorColSize;

	GLuint totalKeyFrames;
	GLuint keyFrameIndex; //, totalPassedFrames;

	GLuint currentAnimationIndex;
	GLuint nextAnimationIndex;

	GLsizei totalAnimationSize;

	std::vector<GLuint> keyFrames; // The Animation2D itself

	//need to use unsigned long long int or is float and int enough?
	unsigned long long int totalAnimationFrameRate;
	unsigned long long int eachAnimationFrameRate;
	unsigned long long int targetAnimationFrameRate;
	unsigned long long int currentFrameRate;

	unsigned long long int totalElapseTimer;
	unsigned long long int currentElapseTimer;

private:

	void updateAnimation(const float& deltaTime_Seconds);


public:

	Animator2D(const GLuint& row, const GLuint& column, const AnimationMode& mode = AnimationMode::ONE_SHOT);
	~Animator2D();

	void update(const float& deltaTime_Seconds);

	void restartAnimation();
	void clearKeyFrame();

	const bool& addKeyFrame(const GLuint& whichRow, const GLuint& whichColumn);
	const bool& addKeyFrame(const GLuint& index);

	const bool& setKeyFrame(const GLuint& size, GLuint* indexs);
	const bool& setKeyFrameOrderDependSize();

	void setAnimationMode(const AnimationMode& mode);
	void setAnimationFrameRate(const GLuint& frameRateInSecond); // One second have how many key frame
	void setAnimationFrameRate(const double& timeOfScenod); // One second have how many key frame

	bool setNextAnimationIndex(const GLuint& index);

	const unsigned long long int& const getAnimationFrameRateInSecond() const;

	const GLuint& const getCurrentKeyFrame() const;
	const GLuint& const getCurrentKeyFrameIndex() const;

	const AnimationMode& const getAnimationMode() const;

	GLuint& getCurrentAnimationIndex();
	GLuint& getNextAnimationIndex();

};
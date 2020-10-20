#include "animator2D.h"

Animator2D::Animator2D(const GLuint& row, const GLuint& column, const AnimationMode& mode) {

	rawAnimationRow = ((row <= 0) ? 1 : row);
	rawAnimationCol = ((column <= 0) ? 1 : column);
	rawTotalAnimationFrame = rawAnimationRow * rawAnimationCol;

	eachNorRowSize = 1.0f / static_cast<float>(rawAnimationRow);
	eachNorColSize = 1.0f / static_cast<float>(rawAnimationCol);

	totalKeyFrames = 0;
	keyFrameIndex = 0;

	totalAnimationFrameRate = 0;
	eachAnimationFrameRate = 0;
	targetAnimationFrameRate = 0;

	currentFrameRate = 0;

	currentAnimationIndex = 0;
	nextAnimationIndex = 0;

	totalAnimationSize = 0;

}

Animator2D::~Animator2D() { }

void Animator2D::updateAnimation(const float& deltaTime_Seconds) {

	//change algorithm to swith case based for future additional animation mode

	if (mode == AnimationMode::ONE_SHOT && keyFrameIndex >= (totalKeyFrames - 1)) { return; }

	currentFrameRate += deltaTime_Seconds;

	while (currentFrameRate >= targetAnimationFrameRate)
	{
		++keyFrameIndex;

		if (currentFrameRate >= totalAnimationFrameRate && mode != AnimationMode::ONE_SHOT)
		{
			keyFrameIndex = 0;
			currentFrameRate -= totalAnimationFrameRate;

		}

		targetAnimationFrameRate = static_cast<unsigned long long int>(keyFrameIndex + 1) * eachAnimationFrameRate;

	}

}

void Animator2D::restartAnimation()
{
	currentFrameRate = 0.0f;
	keyFrameIndex = 0;

	targetAnimationFrameRate = static_cast<double>(keyFrameIndex + 1) * eachAnimationFrameRate;

}

void Animator2D::clearKeyFrame()
{
	keyFrames.clear();
	totalKeyFrames = 0;
}

void Animator2D::update(const float& deltaTime_Seconds) {

	if (currentAnimationIndex != nextAnimationIndex) { return; }

	currentElapseTimer += deltaTime_Seconds;

	if (currentElapseTimer >= totalElapseTimer)
	{
		currentElapseTimer = 0;
		restartAnimation();

		currentAnimationIndex = nextAnimationIndex;
	}

	updateAnimation(deltaTime_Seconds);

}

const bool& Animator2D::addKeyFrame(const GLuint& whichRow, const GLuint& whichColumn)
{
	if (whichRow >= rawAnimationRow || whichColumn >= rawAnimationCol)
	{
		printf("Add animation key frame size wrong!");
		return false;

	}

	keyFrames.push_back((whichColumn * rawAnimationRow) + whichRow);
	keyFrames.shrink_to_fit();

	totalKeyFrames = keyFrames.size();

	return true;

}

const bool& Animator2D::addKeyFrame(const GLuint& index)
{
	if (index >= rawTotalAnimationFrame)
	{
		printf("Add animation key frame size wrong!");
		return false;

	}

	keyFrames.push_back(index);
	keyFrames.shrink_to_fit();

	totalKeyFrames = keyFrames.size();

	return true;

}

const bool& Animator2D::setKeyFrame(const GLuint& size, GLuint* indexs)
{
	if (indexs == nullptr)
	{
		printf("Set animation key frame index pointer are nullptr!");
		return false;

	}

	keyFrames.clear();
	keyFrames.resize(size);
	keyFrames.shrink_to_fit();

	for (size_t i = 0; i < size; i++)
	{
		if (indexs[i] >= rawTotalAnimationFrame)
		{
			keyFrames.clear();
			printf("Set animation key frame index are over the total size!");

			return false;

		}

		keyFrames[i] = indexs[i];

	}


	totalKeyFrames = keyFrames.size();

	return true;

}

const bool& Animator2D::setKeyFrameOrderDependSize()
{
	if (rawTotalAnimationFrame <= 0)
	{
		printf("Set animation key frame order depend size are false, because the total sprite sheet are 0!");
		return false;

	}

	keyFrames.clear();
	keyFrames.resize(rawTotalAnimationFrame);
	keyFrames.shrink_to_fit();

	totalKeyFrames = rawTotalAnimationFrame;

	for (size_t i = 0; i < totalKeyFrames; i++)
	{
		keyFrames[i] = i;

	}

	return true;

}

void Animator2D::setAnimationMode(const AnimationMode& mode)
{
	this->mode = mode;

}

void Animator2D::setAnimationFrameRate(const GLuint& frameRateInSecond)
{
	if (frameRateInSecond == 0) // If this frame rate equals to zero than don't let it process divide
	{
		eachAnimationFrameRate = 0.01f * SECOND_TO_NANOSECOND;
		totalAnimationFrameRate = static_cast<unsigned long long int>(totalKeyFrames) * eachAnimationFrameRate;
		return;

	}

	eachAnimationFrameRate = SECOND_TO_NANOSECOND / static_cast<unsigned long long int>(frameRateInSecond);
	totalAnimationFrameRate = static_cast<unsigned long long int>(totalKeyFrames) * eachAnimationFrameRate;

}

void Animator2D::setAnimationFrameRate(const double& timeOfScenod)
{
	if (timeOfScenod <= 0.0) // If this frame rate equals to zero than don't let it process divide
	{
		eachAnimationFrameRate = 0.01f * SECOND_TO_NANOSECOND;
		totalAnimationFrameRate = static_cast<unsigned long long int>(totalKeyFrames) * eachAnimationFrameRate;
		return;

	}

	eachAnimationFrameRate = timeOfScenod * SECOND_TO_NANOSECOND;
	totalAnimationFrameRate = static_cast<unsigned long long int>(totalKeyFrames) * eachAnimationFrameRate;

	targetAnimationFrameRate = static_cast<unsigned long long int>(keyFrameIndex + 1) * eachAnimationFrameRate;

}

const unsigned long long int& const Animator2D::getAnimationFrameRateInSecond() const { return eachAnimationFrameRate; }

const GLuint& const Animator2D::getCurrentKeyFrame() const { return keyFrames[keyFrameIndex]; }

const GLuint& const Animator2D::getCurrentKeyFrameIndex() const { return keyFrameIndex; }

const Animator2D::AnimationMode& const Animator2D::getAnimationMode() const { return mode; }

bool Animator2D::setNextAnimationIndex(const GLuint& index) {

	if (nextAnimationIndex == index) { return true; }

	if (index >= totalAnimationSize) {
		printf("Set next animation index are false, because the index are over or equals the size!");
		return false;
	}

	//totalElapseTimer = ; //I dont know what to put here
	currentElapseTimer = 0;

	nextAnimationIndex = index;

	printf("currentAnimationIndex = %u, nextAnimationIndex = %u\n", currentAnimationIndex, nextAnimationIndex);

	return true;

}

GLuint& Animator2D::getCurrentAnimationIndex()
{
	return currentAnimationIndex;
}

GLuint& Animator2D::getNextAnimationIndex()
{
	return nextAnimationIndex;
}
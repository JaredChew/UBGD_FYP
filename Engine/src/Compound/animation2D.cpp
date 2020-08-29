#include "Animation2D.h"

#include "../Utilities/timer.h"

#include "../Modules FrontEnd/sprite.h"
#include "../Compound/texture.h"

// ---------------------------------------------------------
// |                  **  Constructors ** 				   |
// ---------------------------------------------------------
Animation2D::Animation2D()
	: animation2DSpriteSheet()
{
	this->animation2DMode = Animation2DMode::OneShot;
	timer = new Timer();

	this->keyFrames.clear();

	this->totalKeyFrames = 0;
	this->keyFrameIndex = 0;

	this->totalAnimationFrameRate = 0;
	this->eachAnimationFrameRate = 0;
	this->targetAnimationFrameRate = 0;

	this->currentFrameRate = 0;

}
Animation2D::Animation2D(Timer* timer, Texture* texture, const GLuint& row, const GLuint& column, const Animation2DMode& mode)
	: animation2DSpriteSheet(row, column, texture), animation2DMode(mode), timer(timer)
{
	this->keyFrames.clear();

	this->totalKeyFrames = 0;
	this->keyFrameIndex = 0;

	this->totalAnimationFrameRate = 0;
	this->eachAnimationFrameRate = 0;
	this->targetAnimationFrameRate = 0;

	this->currentFrameRate = 0;

}
Animation2D::Animation2D(Timer* time, const Animation2DSpriteSheet& info, const Animation2DMode& mode)
	: animation2DSpriteSheet(info), animation2DMode(mode), timer(timer)
{
	this->keyFrames.clear();

	this->totalKeyFrames = 0;
	this->keyFrameIndex = 0;

	this->totalAnimationFrameRate = 0;
	this->eachAnimationFrameRate = 0;
	this->targetAnimationFrameRate = 0;

	this->currentFrameRate = 0;

}
Animation2D::~Animation2D()
{
	this->keyFrames.clear();

}


// ---------------------------------------------------------
// |                  **   Functions   ** 				   |
// ---------------------------------------------------------
void Animation2D::restartAnimation(void)
{
	this->currentFrameRate = 0.0f;
	this->keyFrameIndex = 0;

	this->targetAnimationFrameRate = static_cast<double>(this->keyFrameIndex + 1) * this->eachAnimationFrameRate;

}
void Animation2D::clearKeyFrame()
{
	this->keyFrames.clear();
	this->totalKeyFrames = 0;
}
const bool& Animation2D::addKeyFrame(const GLuint& whichRow, const GLuint& whichColumn)
{
	if (whichRow >= this->animation2DSpriteSheet.rawAnimationRow || whichColumn >= this->animation2DSpriteSheet.rawAnimationCol)
	{
		printf("Add animation key frame size wrong!");
		return false;

	}
	
	this->keyFrames.push_back((whichColumn * this->animation2DSpriteSheet.rawAnimationRow) + whichRow);
	this->keyFrames.shrink_to_fit();

	this->totalKeyFrames = this->keyFrames.size();

	return true;

}
const bool& Animation2D::addKeyFrame(const GLuint& index)
{
	if (index >= this->animation2DSpriteSheet.rawTotalAnimationFrame)
	{
		printf("Add animation key frame size wrong!");
		return false;

	}

	this->keyFrames.push_back(index);
	this->keyFrames.shrink_to_fit();

	this->totalKeyFrames = this->keyFrames.size();

	return true;

}
const bool& Animation2D::setKeyFrame(const GLuint& size, GLuint* indexs)
{
	if (indexs == nullptr)
	{
		printf("Set animation key frame index pointer are nullptr!");
		return false;

	}

	this->keyFrames.clear();
	this->keyFrames.resize(size);
	this->keyFrames.shrink_to_fit();

	for (size_t i = 0; i < size; i++)
	{
		if (indexs[i] >= this->animation2DSpriteSheet.rawTotalAnimationFrame)
		{
			this->keyFrames.clear();
			printf("Set animation key frame index are over the total size!");

			return false;

		}

		this->keyFrames[i] = indexs[i];

	}


	this->totalKeyFrames = this->keyFrames.size();

	return true;

}
const bool& Animation2D::setKeyFrameOrderDependSize(void)
{
	if (animation2DSpriteSheet.rawTotalAnimationFrame <= 0)
	{
		printf("Set animation key frame order depend size are false, because the total sprite sheet are 0!");
		return false;

	}

	this->keyFrames.clear();
	this->keyFrames.resize(animation2DSpriteSheet.rawTotalAnimationFrame);
	this->keyFrames.shrink_to_fit();

	this->totalKeyFrames = animation2DSpriteSheet.rawTotalAnimationFrame;

	for (size_t i = 0; i < this->totalKeyFrames; i++)
	{
		this->keyFrames[i] = i;

	}

	return true;

}


// ---------------------------------------------------------
// |                  **    Setters    ** 				   |
// ---------------------------------------------------------
void Animation2D::setMode(const Animation2DMode& mode)
{
	this->animation2DMode = mode;

}
void Animation2D::setAnimationFrameRate(const GLuint& frameRateInSecond)
{
	if (frameRateInSecond == 0) // If this frame rate equals to zero than don't let it process divide
	{
		this->eachAnimationFrameRate = 0.01f * OneSecondToNanosecond;
		this->totalAnimationFrameRate = static_cast<Nanosecond>(this->totalKeyFrames) * this->eachAnimationFrameRate;
		return;

	}

	this->eachAnimationFrameRate = OneSecondToNanosecond / static_cast<Nanosecond>(frameRateInSecond);
	this->totalAnimationFrameRate = static_cast<Nanosecond>(this->totalKeyFrames) * this->eachAnimationFrameRate;

}
void Animation2D::setAnimationFrameRate(const double& timeOfScenod)
{
	if (timeOfScenod <= 0.0) // If this frame rate equals to zero than don't let it process divide
	{
		this->eachAnimationFrameRate = 0.01f * OneSecondToNanosecond;
		this->totalAnimationFrameRate = static_cast<Nanosecond>(this->totalKeyFrames) * this->eachAnimationFrameRate;
		return;

	}

	this->eachAnimationFrameRate = timeOfScenod * OneSecondToNanosecond;
	this->totalAnimationFrameRate = static_cast<Nanosecond>(this->totalKeyFrames) * this->eachAnimationFrameRate;

	this->targetAnimationFrameRate = static_cast<Nanosecond>(keyFrameIndex + 1) * this->eachAnimationFrameRate;

}


// ---------------------------------------------------------
// |                  **    Getters    ** 				   |
// ---------------------------------------------------------
const Nanosecond& const Animation2D::getAnimationFrameRateInSecond(void) const { return this->eachAnimationFrameRate; }
const GLuint& const Animation2D::getCurrentKeyFrame(void) const { return this->keyFrames[this->keyFrameIndex]; }
const GLuint& const Animation2D::getCurrentKeyFrameIndex() const { return this->keyFrameIndex; }
const Animation2DSpriteSheet& const Animation2D::getAnimation2DSpriteSheet(void) const { return this->animation2DSpriteSheet; }
const Animation2DMode& const Animation2D::getAnimation2DMode(void) const { return this->animation2DMode; }



void Animation2D::update()
{
	if (this->animation2DMode == Animation2DMode::OneShot && this->keyFrameIndex >= (this->totalKeyFrames - 1)) { return; }

	timer->recordTock();
	this->currentFrameRate += timer->getDeltaTime();

	while (this->currentFrameRate >= this->targetAnimationFrameRate)
	{
		++this->keyFrameIndex;

		if (this->currentFrameRate >= this->totalAnimationFrameRate && this->animation2DMode != Animation2DMode::OneShot)
		{
			this->keyFrameIndex = 0;
			this->currentFrameRate -= this->totalAnimationFrameRate;

		}

		this->targetAnimationFrameRate = static_cast<Nanosecond>(this->keyFrameIndex + 1) * this->eachAnimationFrameRate;

	}

	timer->recordTick();

}
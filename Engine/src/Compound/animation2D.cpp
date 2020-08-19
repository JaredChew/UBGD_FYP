#include "Animation2D.h"

#include "../Utilities/timer.h"

#include "../Modules FrontEnd/sprite.h"
#include "../Compound/texture.h"

// ---------------------------------------------------------
// |                  **  Constructors ** 				   |
// ---------------------------------------------------------
Animation2D::Animation2D()
	: animation2DInfo()
{
	this->animation2DMode = Animation2DMode::OneShot;
	timer = new Timer();

	this->keyFrames.clear();
	this->currentKeyFrame = 0;

	this->totalKeyFrames = 0;
	this->currentKeyFrame = 0;

	this->animationFrameRate = 0;

	this->totalAnimationFrameRate = 0;
	this->eachAnimationFrameRate = 0;
	this->currentAnimationFrameRate = 0;

	this->deltaTime = 0;

}
Animation2D::Animation2D(Timer* timer, Texture* texture, const GLuint& row, const GLuint& column, const Animation2DMode& mode)
	: animation2DInfo(row, column, texture), animation2DMode(mode), timer(timer)
{
	this->keyFrames.clear();
	this->currentKeyFrame = 0;

	this->totalKeyFrames = 0;
	this->currentKeyFrame = 0;

	this->animationFrameRate = 0;

	this->totalAnimationFrameRate = 0;
	this->eachAnimationFrameRate = 0;
	this->currentAnimationFrameRate = 0;

	this->deltaTime = 0;

}
Animation2D::Animation2D(Timer* time, const Animation2DInfo& info, const Animation2DMode& mode)
	: animation2DInfo(info), animation2DMode(mode), timer(timer)
{
	this->keyFrames.clear();
	this->currentKeyFrame = 0;

	this->totalKeyFrames = 0;
	this->currentKeyFrame = 0;

	this->animationFrameRate = 0;

	this->totalAnimationFrameRate = 0;
	this->eachAnimationFrameRate = 0;
	this->currentAnimationFrameRate = 0;

	this->deltaTime = 0;

}
Animation2D::~Animation2D()
{
	this->keyFrames.clear();

}


// ---------------------------------------------------------
// |                  **   Functions   ** 				   |
// ---------------------------------------------------------
void Animation2D::clearKeyFrame()
{
	this->keyFrames.clear();
	this->totalKeyFrames = 0;
}
const bool& Animation2D::addKeyFrame(const GLuint& whichRow, const GLuint& whichColumn)
{
	if (whichRow >= this->animation2DInfo.rawAnimationRow || whichColumn >= this->animation2DInfo.rawAnimationCol)
	{
		printf("Add animation key frame size wrong!");
		return false;

	}
	
	int index = (whichRow * this->animation2DInfo.rawAnimationCol) + whichColumn;
	this->keyFrames.push_back(index);
	this->totalKeyFrames = this->keyFrames.size();
	return true;

}
const bool& Animation2D::addKeyFrame(const GLuint& index)
{
	if (index >= this->animation2DInfo.rawTotalAnimationFrame)
	{
		printf("Add animation key frame size wrong!");
		return false;

	}

	this->keyFrames.push_back(index);
	this->totalKeyFrames = this->keyFrames.size();
	return true;

}


// ---------------------------------------------------------
// |                  **    Setters    ** 				   |
// ---------------------------------------------------------
void Animation2D::setMode(const Animation2DMode& mode)
{
	this->animation2DMode = mode;

}
void Animation2D::setAnimationFrameRate(const GLuint& frameRate)
{
	this->animationFrameRate = frameRate;

	if (this->animationFrameRate == 0) // If this frame rate equals to zero than don't let it process divide
	{
		this->eachAnimationFrameRate = 0;
		this->totalAnimationFrameRate = 0;
		return;

	}

	this->eachAnimationFrameRate = OneSecondToNanosecond / this->animationFrameRate;
	this->totalAnimationFrameRate = this->totalKeyFrames * this->eachAnimationFrameRate;

}


// ---------------------------------------------------------
// |                  **    Getters    ** 				   |
// ---------------------------------------------------------
const GLuint& const Animation2D::getAnimationFrameRate() const { return this->animationFrameRate; }
const GLuint& const Animation2D::getCurrentKeyFrame() const { return this->currentKeyFrame; }
const Animation2DInfo& const Animation2D::getAnimation2DInfo() const { return this->animation2DInfo; }
const Animation2DMode& const Animation2D::getAnimation2DMode() const { return this->animation2DMode; }


void Animation2D::update()
{
	if (this->animation2DMode == Animation2DMode::OneShot && this->currentKeyFrame >= this->totalKeyFrames) { return; }

	timer->recordTock();

	deltaTime += timer->getDeltaTime();										// The deltaTime is real nano time passed.
	currentAnimationFrameRate = currentKeyFrame * eachAnimationFrameRate;	// The currentAnimationFrameRate is the fit nano time of the currentKeyFrame passed.

	// If  "real nano passed time"  more than  "fit nano time passed time"  then need to add the currentKeyFrame.
	// Mean if the player driver happen lag 3 animation frame rate, but then the update() function each frame only plus one,
	// that mean player will loss 3 animation frame in this second.
	// So this while loop will see the "real nano passed time" to make sure now are update correctly on the time.
	while (deltaTime >= currentAnimationFrameRate && currentKeyFrame < totalKeyFrames)
	{
		++currentKeyFrame;
		currentAnimationFrameRate = currentKeyFrame * eachAnimationFrameRate;
		
		// If the deltaTime are more than totalKeyFrames + 1, then will set currentKeyFrame to zero and check the while loop again.
		// Example: deltaTime = 50; totalAnimationFrameRate = 40; eachAnimationFrameRate = 10;
		//				50 more than or equal to 40 + 10 is true
		// That mean now the currentFrame should be 0 not the last key frame, 
		// but the while loop condition (currentKeyFrame < totalKeyFrames) will let it stop at totalKeyFrame.
		// So this one can let the while loop keep going while the deltaTime are over than totalAnimationFrameRate + eachAnimationFrameRate.
		if (deltaTime >= (totalAnimationFrameRate + eachAnimationFrameRate) && animation2DMode != Animation2DMode::OneShot)// && currentKeyFrame >= totalKeyFrames)
		{
			currentKeyFrame = 0;
			deltaTime -= totalAnimationFrameRate;

			currentAnimationFrameRate = currentKeyFrame * eachAnimationFrameRate;
		}
	}
	
	// Render here or dont also can, not sure where better
	/*
	if (currentKeyFrame >= totalKeyFrames && animation2DMode != Animation2DMode::OneShot)
	{
		currentKeyFrame = 0;
		deltaTime -= totalAnimationFrameRate;
	}
	*/
	timer->recordTick();

	/*
	if (totalFramesPassed >= animationFrameRate && deltaTime < OneSecondToNanosecond) {

		renderSprite(mvpMatrix, animationRow, animationCol);

		++animationFrame;
		++animationRow;

		if (animationRow >= sheetRow) {
			++animationCol;
			animationRow = 0;
		}

		deltaTime = 0;

	}

	if (deltaTime >= OneSecondToNanosecond) { deltaTime -= OneSecondToNanosecond; }

	timer->recordTick();

	if (!isAnimationOneShot && animationFrame >= totalAnimationFrames) { animationFrame = 0; }

	++totalFramesPassed;

	++currentAnimationFrame;
	*/
}
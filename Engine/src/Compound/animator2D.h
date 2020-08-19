#pragma once

#include "animation2D.h"


class Animator2D
{
private:
	std::vector<Animation2D> animation2Ds;
	GLuint currentAnimationIndex;

public:
	Animator2D();
	Animator2D(Animation2D* animation2Ds, GLuint size);
	~Animator2D();

	void addAnimation(Animation2D& animation);
	void addAnimations(Animation2D* animation2Ds, GLuint size);
	void setAnimations(Animation2D* animation2Ds, GLuint size);

	const Animation2D& getAnimation2D(GLuint id);

	void update();
};

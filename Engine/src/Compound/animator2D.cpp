#include "animator2D.h"

#include "../Modules FrontEnd/sprite.h"
#include "../Compound/transform.h"

Animator2D::Animator2D()
{
	this->animation2Ds.clear();
	currentAnimationIndex = 0;
}

Animator2D::Animator2D(Animation2D* animation2Ds, GLuint size)
{
	setAnimations(animation2Ds, size);
	currentAnimationIndex = 0;
}

Animator2D::~Animator2D()
{
	this->animation2Ds.clear();
}

void Animator2D::addAnimation(Animation2D& animation)
{
	this->animation2Ds.push_back(animation);

	this->animation2Ds.shrink_to_fit();

}
void Animator2D::addAnimations(Animation2D* animation2Ds, GLuint size)
{
	if (animation2Ds == nullptr) return;

	for (size_t i = 0; i < size; i++)
	{
		this->animation2Ds.push_back(animation2Ds[i]);
	}

	this->animation2Ds.shrink_to_fit();

}

void Animator2D::setAnimations(Animation2D* animation2Ds, GLuint size)
{
	if (animation2Ds == nullptr) return;

	if (this->animation2Ds.size() != size) this->animation2Ds.resize(size);

	for (size_t i = 0; i < size; i++)
	{
		this->animation2Ds[i] = animation2Ds[i];
	}

	this->animation2Ds.shrink_to_fit();

}

void Animator2D::update()
{
	animation2Ds[currentAnimationIndex].update();
}

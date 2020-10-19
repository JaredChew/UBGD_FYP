#include "animator2D.h"

#include "../Utilities/timer.h"

#include "../Compound/transform.h"

Animator2D::Animator2D()
{
	timer = new Timer();

	m_animation2DInfos.clear();

	m_currentAnimationIndex = 0;
	m_nextAnimationIndex = 0;

	m_totalAnimationSize = 0;

}

Animator2D::Animator2D(Timer* timer) :
	timer(timer)
{
	m_animation2DInfos.clear();

	m_currentAnimationIndex = 0;
	m_nextAnimationIndex = 0;

	m_totalAnimationSize = 0;

}

Animator2D::~Animator2D()
{
}

bool Animator2D::addAnimation2DInfo(const Animation2DInfo& animation2DInfo)
{
	if (animation2DInfo.m_animation2D == nullptr)
	{
		printf("Set animation to animator pointer are nullptr!");
		return false;
	}

	m_animation2DInfos.push_back(animation2DInfo);
	m_animation2DInfos.shrink_to_fit();

	m_totalAnimationSize++;

	return true;
}

bool Animator2D::setAnimation2DInfos(const GLuint& size, Animation2DInfo* animation2DInfos)
{
	if (animation2DInfos == nullptr)
	{
		printf("Set animation to animator pointer are nullptr!");
		return false;
	}

	m_totalAnimationSize = size;
	m_animation2DInfos.resize(m_totalAnimationSize);
	m_animation2DInfos.shrink_to_fit();

	for (size_t i = 0; i < m_totalAnimationSize; i++)
	{
		//m_animation2DInfos[i] = animation2DInfos[i]; //uncomment for proper use, commented for test with no error build
	}

	return true;
}

bool Animator2D::setNextAnimationIndex(const GLuint& index)
{
	if (m_nextAnimationIndex == index) return true;

	if (index >= m_totalAnimationSize)
	{
		printf("Set next animation index are false, because the index are over or equals the size!");
		return false;
	}

	m_animation2D_TotalElapseTimer = m_animation2DInfos[m_currentAnimationIndex].m_elapseTime;
	m_animation2D_CurrentElapseTimer = 0;

	m_nextAnimationIndex = index;
	printf("currentAnimationIndex = %u, nextAnimationIndex = %u\n", m_currentAnimationIndex, m_nextAnimationIndex);

	return true;
}

void Animator2D::update()
{
	//printf("currentAnimationIndex = %u, nextAnimationIndex = %u\n", m_currentAnimationIndex, m_nextAnimationIndex);
	timer->recordTock();

	if (m_currentAnimationIndex != m_nextAnimationIndex)
	{
		m_animation2D_CurrentElapseTimer += timer->getDeltaTime();

		if (m_animation2D_CurrentElapseTimer >= m_animation2D_TotalElapseTimer)
		{
			m_animation2D_CurrentElapseTimer = 0;
			m_animation2DInfos[m_currentAnimationIndex].m_animation2D->restartAnimation();

			m_currentAnimationIndex = m_nextAnimationIndex;
		}
	}

	m_animation2DInfos[m_currentAnimationIndex].m_animation2D->update();
	timer->recordTick();
}

Animation2D& Animator2D::getCurrentAnimation2D()
{
	return *m_animation2DInfos[m_currentAnimationIndex].m_animation2D.get();
}

GLuint& Animator2D::getCurrentAnimationIndex()
{
	return m_currentAnimationIndex;
}

GLuint& Animator2D::getNextAnimationIndex()
{
	return m_nextAnimationIndex;
}
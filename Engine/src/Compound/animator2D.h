#pragma once

#include "animation2D.h"
#include <memory>

class Timer;

struct Animation2DInfo
{
public:
	std::shared_ptr<Animation2D> m_animation2D;
	Nanosecond m_elapseTime;

public:
	Animation2DInfo()
	{
		m_animation2D = nullptr;
		m_elapseTime = 0;
	}
	Animation2DInfo(Animation2D& animation2D, const Nanosecond& elapseTime = 0)
	{
		m_animation2D = std::make_shared<Animation2D>(animation2D);
		m_elapseTime = ((elapseTime < 0.0f) ? 0.0f : elapseTime);
	}
	Animation2DInfo(Animation2D* animation2D, const Nanosecond& elapseTime = 0)
	{
		m_animation2D = std::shared_ptr<Animation2D>(animation2D);
		m_elapseTime = ((elapseTime < 0) ? 0 : elapseTime);
	}
	~Animation2DInfo()
	{

	}

};

class Animator2D
{
private:
	std::vector<Animation2DInfo> m_animation2DInfos;

	GLuint m_currentAnimationIndex;
	GLuint m_nextAnimationIndex;

	GLsizei m_totalAnimationSize;

	Nanosecond m_animation2D_TotalElapseTimer;
	Nanosecond m_animation2D_CurrentElapseTimer;

	Timer* timer;

public:
	Animator2D();
	Animator2D(Timer* timer);
	~Animator2D();

	bool addAnimation2DInfo(const Animation2DInfo& animation2DInfo);
	bool setAnimation2DInfos(const GLuint& size, Animation2DInfo* animation2DInfos);

	bool setNextAnimationIndex(const GLuint& index);

	void update();

	Animation2D& getCurrentAnimation2D();
	GLuint& getCurrentAnimationIndex();
	GLuint& getNextAnimationIndex();

};

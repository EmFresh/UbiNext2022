#pragma once
#include "Component.h"
class Bullet :
	public util::Component
{
public:

	void update(float);


	void draw();
	void setDirection(util::Vec3 dir) { m_dir = dir.normal(); }
	void setSpeed(float speed) { m_speed = speed; }
private:
	util::Vec3 m_dir;
	float m_speed;
	float m_duration=0;
};


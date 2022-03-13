#pragma once
#include "Renderer.h"
#include "Gravity.h"

class Wall : public Renderer
{
public:
	void awake();
	virtual void draw();

	void setPosition(util::Vec2 p1, util::Vec2 p2);
	void setPullForce(float);
private:

	util::Vec2 m_begin{0,0}, m_end{0,0};
	float m_length;
	std::vector<Gravity* >m_gravityList;
};


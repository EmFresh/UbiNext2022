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

	util::Vec2 getLineBegin() { return m_begin; }
	util::Vec2 getLineEnd() { return m_end; }
private:

	util::Vec2 m_begin{0,0}, m_end{0,0};
	float m_length;
	std::vector<Gravity* >m_gravityList;
};


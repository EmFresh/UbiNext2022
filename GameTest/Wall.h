#pragma once
#include "Renderer.h"
#include "Gravity.h"

class Wall : public Renderer
{
public:
	void awake();
	virtual void draw();

	void setLength(float);
private:
	float m_length;
	std::vector<Gravity* >m_gravityList;
};


#pragma once
#include "Utilities.h"
#include "Component.h"

class Physics : public util::Component
{
public:

	void awake();

	void lateUpdate(float);

	void addForce(util::Vec3);

private:
	float m_dragPercent = 0;
	util::Vec3 m_force,m_velocity;

};


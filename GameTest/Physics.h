#pragma once
#include "Utilities.h"
#include "Component.h"

class Physics : public util::Component
{
public:

	void awake();

	void lateUpdate(float);

	void addForce(util::Vec3);

	/// <summary>
	/// set the drag of the object with percentage 
	/// from 0 -> 1 (1 is no movement).
	/// </summary>
	/// <param name=""></param>
	void setDragPercent(float);

	void setVelocityCap(float);
private:
	float m_dragPercent = 0,m_velcap=1;
	util::Vec3 m_force,m_velocity;

};


#pragma once
#include "Utilities.h"
#include "Component.h"

class Gravity : public util::Component
{
public:

	void awake();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt:">change in time</param>
	void update(float);
	
	void setPullForce(float);
	static void setWorldGravity(util::Vec3);

private:
	float m_gravPull = 0;

};


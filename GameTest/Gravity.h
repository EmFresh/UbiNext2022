#pragma once
#include "Utilities.h"
#include "Transformer.h"

class Gravity : public util::Transformer
{
public:
	Gravity();
	Gravity(Gravity&);
	Gravity(const Gravity&);

	void awake();


	void update(float);
	
	void setPullForce(float);
	static void setWorldGravity(util::Vec3);

private:
	float m_gravPull = 0;

};


#pragma once
#include "Component.h"

class Renderer :
	public util::Component
{
	virtual void lateUpdate(float dt) { draw(); }
	virtual void draw()=0;
};


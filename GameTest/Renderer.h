#pragma once
#include <functional>
#include "Component.h"
#include "GameObject.h"

class Renderer :
	public util::Component
{
public:
	virtual void lateUpdate(float dt) {  }
	virtual void draw() { if(!getGameObject()->isActive())return; if(m_render)m_render(getGameObject()); };

	void setCustumRender(std::function<void(util::GameObject*)>);
private:
	std::function<void(util::GameObject*)> m_render;
};


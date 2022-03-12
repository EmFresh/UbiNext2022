#pragma once
#include <vector>
#include "Component.h"
#include "Transformer.h"

namespace util
{

class GameObject
{
public:
	GameObject()
	{
		m_components.push_back(new Transformer);
	}
	virtual void awake() { for(auto& comp : m_components)comp->awake(); }
	virtual void start() { for(auto& comp : m_components)comp->start(); }
	virtual void update() { for(auto& comp : m_components)comp->update(); }

	void setActive(bool active) { m_active = active; }
	template<class T>
	T getComponent() { for(auto& comp : m_components) if(dynamic_cast<T*>(comp))return *dynamic_cast<T*>(comp); }

	Transformer getComponent() { return static_cast<Transformer&>(*m_components[0]); }

private:
	bool m_active = true;
	std::vector<Component*> m_components;
};

}

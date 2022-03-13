#include "stdafx.h"
#include "GameObject.h"

namespace util
{


	void GameObject::awake() {}

	void GameObject::start()
	{
		for(auto comp : m_components)comp->start();
	}

	void GameObject::update(float dt)
	{
		for(auto comp : m_components)comp->update(dt);
	}

	void GameObject::lateUpdate(float dt)
	{
		for(auto comp : m_components)comp->lateUpdate(dt);
	}

	void GameObject::setActive(bool active)
	{
		m_active = active;
	}

	bool GameObject::isActive()
	{
		return m_active;
	}

	

	Transformer* GameObject::getComponent()
	{
		return (Transformer*)m_components[0];
	}


}
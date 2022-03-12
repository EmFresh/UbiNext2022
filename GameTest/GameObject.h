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
		~GameObject()
		{
			for(auto a : m_components)
				delete a;
		}

		virtual void awake() { for(auto& comp : m_components)comp->awake(); }
		virtual void start() { for(auto& comp : m_components)comp->start(); }
		virtual void update(float dt) { for(auto& comp : m_components)comp->update(dt); }
		virtual void lateUpdate(float dt) { for(auto& comp : m_components)comp->lateUpdate(dt); }

		void setActive(bool active) { m_active = active; }
		bool isActive() { return m_active; }

		template<class T>
		T* getComponent() { for(auto& comp : m_components) if(dynamic_cast<T*>(comp))return dynamic_cast<T*>(comp); return nullptr; }
		Transformer* getComponent() { return (Transformer*)m_components[0]; }
		template<class T>
		void addComponent(Component* comp = nullptr) { comp ? m_components.push_back(comp) : m_components.push_back(new T()); ((Component*)m_components.back())->setGameObject(this); }

	private:
		bool m_active = true;
		std::vector<Component*> m_components;
	};

}

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
			addComponent<Transformer>();

		}

		~GameObject()
		{
			for(auto a : m_components)
				delete a;
		}

		virtual void awake();
		virtual void start();
		virtual void update(float dt);
		virtual void lateUpdate(float dt);

		void setActive(bool active);
		bool isActive();

		template<class T>
		T* getComponent();
		Transformer* getComponent();

		template<class T>
		std::vector<T*> getComponents();


		template<class T>
		T* addComponent(Component* comp = nullptr);

	private:
		bool m_active = true;
		std::vector<Component*> m_components;
	};


	//templated functions stay in .h file
	template<class T>
	T* GameObject::getComponent()
	{
		for(auto& comp : m_components) if(dynamic_cast<T*>(comp))return dynamic_cast<T*>(comp); return nullptr;
	}

	template<class T>
	inline std::vector<T*> GameObject::getComponents()
	{
		std::vector<T*>list;
		for(auto comp : m_components)
			if(dynamic_cast<T*>(comp))
				list.push_back(comp);

		return list;
	}

	template<class T>
	T* GameObject::addComponent(Component* comp)
	{
		comp ? m_components.push_back(comp) : m_components.push_back(new T());
		auto mycomponent = m_components.back();
		mycomponent->setGameObject(this);
		mycomponent->awake();
		return (T*)mycomponent;
	}


}

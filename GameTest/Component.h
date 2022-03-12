#pragma once
#include "Utilities.h"

namespace util
{
	class GameObject;

	//basically what unity has
	class Component
	{
	public:
		virtual ~Component() = 0 { m_compList.erase(std::find(m_compList.begin(), m_compList.end(), this)); }

		virtual void awake() {}
		virtual void start() {}
		virtual void update(float dt) {}
		virtual void lateUpdate(float dt) {}


		typedef uint CompID;
		virtual CompID createID()
		{

			CompID tmp = 0;
			CompID id = 1;


			for(auto comp : m_compList)
			{

				if(!comp->getID())continue;

				if((comp->getID() - tmp) < 2)
					tmp = comp->getID();
				else
				{
					id = ++tmp;
					return id;
				}
			}

			id = tmp ? tmp + 1 : id;
			return id;


		}

		CompID getID()const { return m_id; }

		GameObject& getGameObject() { return *m_gameObject; }
		void setGameObject(GameObject* go) { m_gameObject = go; }
		template<class T>
		static std::vector<Component*> getComponents()
		{
			std::vector<Component*> result;
			for(auto a : m_compList)
				if(dynamic_cast<T*>(a))
					result.push_back(a);

			return result;
		}
		static std::vector<Component*> getAllComponents() { return m_compList; }
	protected:
		Component() { m_id = createID(); m_compList.push_back(this); }

	private:
		CompID m_id = 0;
		static std::vector<Component*> m_compList;
		GameObject* m_gameObject;
	};
}


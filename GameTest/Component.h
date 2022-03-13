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

		/// <summary>
		/// First function to be called only once. Used like a constructor.
		/// </summary>
		virtual void awake() {}
		/// <summary>
		/// First call before the update loops called only once.
		/// </summary>
		virtual void start() {}
		/// <summary>
		/// Loop of logic done before most physics calculations.
		/// </summary>
		/// <param name="dt:"></param>
		virtual void update(float dt) {}
		/// <summary>
		/// Loop of logic done before rendering.
		/// </summary>
		/// <param name="dt:"></param>
		virtual void lateUpdate(float dt) {}


		typedef uint CompID;

		CompID getID()const { return m_id; }

		GameObject* getGameObject() { return m_gameObject; }
		void setGameObject(GameObject* go) { m_gameObject = go; }
		template<class T>
		static std::vector<T*> getComponents()
		{
			std::vector<T*> result;
			for(auto a : m_compList)
				if(dynamic_cast<T*>(a))
					result.push_back((T*)a);

			return result;
		}
		static std::vector<Component*> getAllComponents() { return m_compList; }
	protected:
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
		Component() { m_id = createID(); m_compList.push_back(this); }

	private:
		CompID m_id = 0;
		static std::vector<Component*> m_compList;
		GameObject* m_gameObject;
	};
}


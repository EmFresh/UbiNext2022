#pragma once
#include "Utilities.h"
#include "GameObject.h"

namespace util
{


	class ObjectPool
	{
	private:
		uint capacity = 0;
		uint count = 0;
		uint current = 0;
		std::vector<GameObject*> objects;
		GameObject m_inst;


	public:

		ObjectPool(uint cap = 10, GameObject inst = GameObject()) { setCapacity(cap); m_inst = inst; }

		/// <summary>
		/// sets the pool capacity
		/// </summary>
		/// <param name="cap"></param>
		void setCapacity(uint cap) { capacity = std::max(cap, (uint)1); count = 0; capacity < objects.size() ? objects.resize(cap) : void(); }

		/// <summary>
		/// gets the next object in the pool and sets it to default
		/// </summary>
		/// <returns></returns>
		GameObject& getNewObject()
		{
			count %= capacity;

			if(count >= objects.size())
				objects.push_back(new GameObject(m_inst));

			objects[current = count]->setActive(true);

			return *objects[current = count++];
		}

		/// <summary>
		/// gets the reference of the current object in the pool
		/// </summary>
		/// <returns></returns>
		GameObject& getCurrentObject() { return *objects[current]; }

		void removeObject(uint index) { objects[index]->setActive(false); }
		void removeObject(GameObject* index) { auto a = std::find(objects.begin(), objects.end(), index); (*a)->setActive(false); }

		std::vector<GameObject*>& getObjectList() { return objects; }
	};
}



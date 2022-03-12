#pragma once
#include "Utilities.h"
//basically what unity has
namespace util
{

	class Component
	{
	public:

		virtual void awake() {}
		virtual void start() {}
		virtual void update() {}


		typedef uint CompID;
		virtual CompID createID()
		{
			
			CompID tmp = 0;
			CompID id = 1;
			

			for(auto comp :m_compList)
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
			
			
			return 0;
		}

		CompID getID()const { return m_id; }
	protected:
		Component() { m_id = createID(); m_compList.push_back(this); }
		virtual ~Component() = 0 { m_compList.erase(std::find(m_compList.begin(), m_compList.end(), this)); }
	private:

		CompID m_id = 0;
		static std::vector<Component*> m_compList;
	};
}


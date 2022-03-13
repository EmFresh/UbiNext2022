//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <vector>
//------------------------------------------------------------------------
#include "app\app.h"
#include "Utilities.h"
#include "GameObject.h"
#include "Wall.h"
//------------------------------------------------------------------------

using util::Vec3;
using util::Transformer;
using util::GameObject;
using std::vector;



//------------------------------------------------------------------------
#define MyGame
#ifdef MyGame
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------

vector<GameObject*> m_addlist, m_drawlist;
void Init()
{
	GameObject* obj;
	m_addlist.push_back(obj = new GameObject());
	auto wall = obj->addComponent<Wall>();
	wall->setLength(300);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float dt)
{
	//add new GameObjects
	if(m_addlist.size())
	{
		for(auto a : m_addlist)
			m_drawlist.push_back(a);


		for(auto a : m_addlist)
			a->start();

		m_addlist.clear();
	}

	//Extra logic goes here






	//update loops
	for(auto a : m_drawlist)
		a->update(dt);

	for(auto a : m_drawlist)
		a->lateUpdate(dt);

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	for(auto a : m_drawlist)
		a->getComponent<Renderer>()->draw();

}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

}
#endif // MyGame
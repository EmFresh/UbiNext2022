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
	float lengths[]{300, 300, 300, 300, 300};
	Vec3 positions[]{{200, 400}, {200, 200}, {200, 200}, {200, 200}, {200, 200}, };
	Vec3 rotations[]{{0, 0, 90 + 45}, {0, 0, 90 + 45}, {0, 0, 90 + 45}, {0, 0, 90 + 45}, {0, 0, 90 + 45}, };

	for(int a = 0; a < 5; ++a)
	{
		m_addlist.push_back(obj = new GameObject());
		auto trans = obj->getComponent<Transformer>();
		auto wall = obj->addComponent<Wall>();

		wall->setPullForce(5);
		wall->setLength(lengths[a]);
		trans->translate(positions[a]);
		trans->rotateBy(rotations[a]);

	}





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
	{
		auto render = a->getComponent<Renderer>();
		if(render)
			render->draw();
	}
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

}
#endif // MyGame
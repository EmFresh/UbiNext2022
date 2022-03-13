//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <vector>
#include <fstream>
#include <filesystem>
//------------------------------------------------------------------------
#include "app\app.h"
#include "Utilities.h"
#include "GameObject.h"
#include "Wall.h"
#include "Player.h"
#include "Physics.h"
#include "Quat.h"
//------------------------------------------------------------------------

using util::Vec4;
using util::Vec3;
using util::Vec2;
using util::Transformer;
using util::GameObject;


using std::vector;

namespace fs = std::filesystem;

/*********************************
Game Premise:
A lone man with a ship... enemies
all around... can you survive? 
Everything has gravity, the floor,
the enemies, and yes even you. 
Fight against enemies under terminal 
gravity for your survival. as time
increases so does your gravity making 
it easier for enemies to catch you. 

***********************************/



//------------------------------------------------------------------------
#define MyGame
#ifdef MyGame
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------



// LINE/LINE
bool lineLine(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4)
{

	// calculate the distance to intersection point
	float uA = ((v4.x - v3.x) * (v1.y - v3.y) - (v4.y - v3.y) * (v1.x - v3.x)) / ((v4.y - v3.y) * (v2.x - v1.x) - (v4.x - v3.x) * (v2.y - v1.y));
	float uB = ((v2.x - v1.x) * (v1.y - v3.y) - (v2.y - v1.y) * (v1.x - v3.x)) / ((v4.y - v3.y) * (v2.x - v1.x) - (v4.x - v3.x) * (v2.y - v1.y));

	// if uA and uB are between 0-1, lines are colliding
	return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
	
}


// POINT/CIRCLE
bool pointInCircle(Vec2 ptoc, float r)
{

	// get distance between the point and circle's center
	// using the Pythagorean Theorem


	// if the distance is less than the circle's
	// radius the point is inside!

	return  ptoc.length() <= r;

}


// LINE/POINT
bool lineInPoint(Vec2 v1, Vec2 v2, Vec2 point)
{

	// get distance from the point to the two ends of the line
	float d1 = Vec2::distance(point, v1);
	float d2 = Vec2::distance(point, v2);

	// get the length of the line
	float lineLen = Vec2::distance(v1, v2);

	// since floats are so minutely accurate, add
	// a little buffer zone that will give collision
	float buffer = 0.01f;    // higher # = less accurate

	// if the two distances are equal to the line's
	// length, the point is on the line!
	// note we use the buffer here to give a range,
	// rather than one #

	return (d1 + d2) >= (lineLen - buffer) && (d1 + d2) <= (lineLen + buffer);

}

// LINE/CIRCLE
boolean lineCircle(Vec2 p1, Vec2 p2, Vec2 c, float r)
{

	// is either end INSIDE the circle?
	// if so, return true immediately
	if(pointInCircle(p1 - c, r) || pointInCircle(p2 - c, r)) return true;

	// get length of the line
	float len = (p1 - p2).length();

	// get dot product of the line and circle
	float dot = (((c.x - p1.x) * (p2.x - p1.x)) + ((c.y - p1.y) * (p2.y - p1.y))) / powf(len, 2);

	// find the closest point on the line
	Vec2 closest = p1 + (dot * (p2 - p1));

	// is this point actually on the line segment?
	// if so keep going, but if not, return false
	bool onSegment = lineInPoint(p1, p2, closest);
	if(!onSegment) return false;


	// get distance to closest point
	return  (closest - c).length() <= r;
}




vector<GameObject*> m_addlist, m_drawlist;

void readFile(std::string path)
{

	GameObject* obj;
	std::ifstream file(path);
	std::string line = "";

	for(auto a : m_drawlist)
		delete a;
	m_drawlist.clear();


	//add player 
	m_addlist.push_back(obj = new GameObject());
	auto trans = obj->getComponent<Transformer>();
	auto player = obj->addComponent<Player>();
	auto grav = obj->addComponent<Gravity>();
	auto phy = obj->addComponent<Physics>();
	auto rend = obj->addComponent<Renderer>();

	trans->translate({APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT/2});
	rend->setCustumRender([](GameObject* obj)
		{
			auto trans = obj->getComponent<Transformer>();
			auto player= obj->getComponent<Player>();
			Vec4 pos = trans->getWorldTransformation() * (trans->getLocalTransformation() * Vec4(0, 0, 0, 1));

			float rad = 35;

			Vec4 
				p1 = trans->getWorldRotationMatrix() * trans->getWorldScaleMatrix() * (trans->getLocalRotationMatrix() * trans->getLocalScaleMatrix() * util::Quat::quatRotationMat(0, {0, 0, 1}) * Vec4(0, 1, 0) * rad),
				p2 = trans->getWorldRotationMatrix() * trans->getWorldScaleMatrix() * (trans->getLocalRotationMatrix() * trans->getLocalScaleMatrix() * util::Quat::quatRotationMat(360.f / 3, {0, 0, 1}) * Vec4(0, 1, 0) * rad),
				p3 = trans->getWorldRotationMatrix() * trans->getWorldScaleMatrix() * (trans->getLocalRotationMatrix() * trans->getLocalScaleMatrix() * util::Quat::quatRotationMat(360.f / 3 * 2, {0, 0, 1}) * Vec4(0, 1, 0) * rad);

			p1 += pos;
			p2 += pos;
			p3 += pos;

			//draw triangle
			auto tmp1=p1+trans->getUp()*1;
			auto tmp2=util::lerp(p1,p2,.1f);
			auto tmp3=util::lerp(p1,p3,.1f);

			App::DrawLine(p1.x, p1.y, p2.x, p2.y);
			App::DrawLine(p2.x, p2.y, p3.x, p3.y);
			App::DrawLine(p3.x, p3.y, p1.x, p1.y);
			App::DrawLine(p1.x, p1.y, tmp2.x, tmp2.y,1,0,0);
			App::DrawLine(p1.x, p1.y, tmp3.x, tmp3.y,1,0,0);
			App::Print(APP_VIRTUAL_WIDTH / 2-100, APP_VIRTUAL_HEIGHT - 50,std::to_string((int)player->getFuel()).c_str());
			

		});
	grav->setPullForce(5);
	phy->setDragPercent(0.01f);
	phy->setVelocityCap(1);
	player->setDriveForce(.03f);

	while(std::getline(file, line))
	{
		if(line.substr(0, line.find(':')) == "wall")
		{
			m_addlist.push_back(obj = new GameObject());
			trans = obj->getComponent<Transformer>();
			auto wall = obj->addComponent<Wall>();
			float x1, y1, x2, y2;


			//force
			line = line.substr(line.find(' ') + 1);
			line = line.substr(line.find_first_not_of(' '));
			wall->setPullForce(std::stof(line.substr(0, line.find(' '))));


			//position 1
			line = line.substr(line.find('{') + 1);
			line = line.substr(line.find_first_not_of(' '));
			x1 = std::stof(line.substr(0, line.find(',')));
			line = line.substr(line.find(',') + 1);
			line = line.substr(line.find_first_not_of(' '));
			y1 = std::stof(line.substr(0, line.find('}')));


			//position 2
			line = line.substr(line.find('{') + 1);
			line = line.substr(line.find_first_not_of(' '));
			x2 = std::stof(line.substr(0, line.find(',')));
			line = line.substr(line.find(',') + 1);
			line = line.substr(line.find_first_not_of(' '));
			y2 = std::stof(line.substr(0, line.find('}')));

			wall->setPosition({x1, y1}, {x2, y2});
		}
	}

	file.close();
}

void Init()
{

	//readFile("level 0.data");



}

fs::file_time_type lastTime = fs::file_time_type();

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


	if(fs::last_write_time(fs::path("level 0.data")) != lastTime)
	{
		readFile("level 0.data");
		lastTime = fs::last_write_time(fs::path("level 0.data"));
	}


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
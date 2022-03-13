#include "stdafx.h"
#include "Wall.h"
#include "GameObject.h"
#include "Transformer.h"

#include "App/app.h"

using util::Transformer;
using util::Vec3;
using util::Vec4;

void Wall::awake()
{
	m_gravityList.push_back(getGameObject()->addComponent<Gravity>());
	m_gravityList.push_back(getGameObject()->addComponent<Gravity>());
	m_gravityList.push_back(getGameObject()->addComponent<Gravity>());


}

void Wall::draw()
{
	if(!getGameObject()->isActive())return;

	auto trans = getGameObject()->getComponent<Transformer>();

	Vec4 worldPos = trans->getWorldTranslationMatrix() * (trans->getLocalTranslationMatrix() * Vec4(0, 0, 0, 1));



	auto end = worldPos + Vec4(trans->getUp() * m_length, 1);

	App::DrawLine(worldPos.x, worldPos.y, end.x, end.y, 1, 0, 0);


	////for testing
	//for(auto a : m_gravityList)
	//{
	//	auto trans2 = (Transformer*)a;
	//	worldPos = trans2->getWorldTransformation() * (trans2->getLocalTransformation() * Vec4(0, 0, 0, 1));
	//	end = worldPos + trans2->getWorldRotationMatrix()*Vec4(trans2->getUp() * 50, 0);
	//
	//	App::DrawLine(worldPos.x, worldPos.y, end.x, end.y, 0, 1, 0);
	//}



	App::Print(0, 300, end.toString());
}

void Wall::setLength(float length)
{
	m_length = length;

	for(int a = 0; a < m_gravityList.size(); ++a)
	{
		auto gravityPoint = util::lerp(Vec3(0, 0, 0), Vec3(0, 1, 0) * length, (float)a / (m_gravityList.size() - 1));
		m_gravityList[a]->translate(gravityPoint.x, gravityPoint.y, 0);
	}
}

void Wall::setPullForce(float pull)
{
	float force = pull / m_gravityList.size();
	for(auto a : m_gravityList)
		a->setPullForce(force);
}

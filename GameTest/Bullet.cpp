#include "stdafx.h"
#include "App/app.h"
#include "Bullet.h"
#include "Transformer.h"
#include "GameObject.h"

using util::Transformer;
using util::GameObject;

void Bullet::update(float dt)
{
	if(m_duration > 10)
	{
		getGameObject()->setActive(false);
		m_duration = 0;
	}
	
	if(!getGameObject()->isActive())return;
	m_duration += dt;

	auto trans = getGameObject()->getComponent<Transformer>();
	trans->translateBy(m_dir * m_speed * dt);
	auto pos = trans->getLocalPosition();

	//check for collisions


}

void Bullet::draw()
{
	if(!getGameObject()->isActive())return;
	auto trans = getGameObject()->getComponent<Transformer>();
	auto pos = trans->getLocalPosition();

	//draw bullet
	float bulletLength = 5;
	App::DrawLine(pos.x, pos.y,
		(pos.x - m_dir.normal().x * bulletLength),
		(pos.y - m_dir.normal().y * bulletLength), 1, 0, 0);
}

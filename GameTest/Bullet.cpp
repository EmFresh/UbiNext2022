#include "stdafx.h"
#include "App/app.h"
#include "Bullet.h"
#include "Transformer.h"
#include "GameObject.h"

using util::Transformer;
using util::GameObject;

void Bullet::update(float dt)
{
	if(!getGameObject()->isActive())return;
	if(m_duration > 2)
	{
		getGameObject()->setActive(false);
		m_duration = 0;
	}
	auto trans = getGameObject()->getComponent<Transformer>();
	trans->translateBy(m_dir * m_speed * dt);
	auto pos = trans->getLocalPosition();

	//check for collisions

	//draw bullet
	float bulletLength = 5;
	App::DrawLine(pos.x, pos.y,
		(pos.x - m_dir.normal().x * bulletLength),
		(pos.y - m_dir.normal().y * bulletLength), 1, 0, 0);
	m_duration += dt;
}

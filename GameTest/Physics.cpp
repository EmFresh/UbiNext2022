#include "stdafx.h"
#include "Physics.h"
#include "GameObject.h"

using util::Vec3;
using util::GameObject;
using util::Transformer;

void Physics::awake()
{
	m_force = Vec3(0);
	m_velocity = Vec3(0);
}

void Physics::lateUpdate(float dt)
{
	if(!getGameObject()->isActive())return;


	m_velocity += m_force;
	m_velocity *= util::clamp<float>(0, 1, 1 - m_dragPercent);

	m_velocity = util::clamp<float>(0,m_velcap,m_velocity.length())*m_velocity.normal();
	getGameObject()->getComponent<Transformer>()->translateBy(m_velocity * dt);

	m_force = Vec3(0);
}

void Physics::addForce(util::Vec3 force)
{
	if(!getGameObject()->isActive())return;

	m_force += force;

}

void Physics::setDragPercent(float percent)
{
	m_dragPercent = percent;
}

void Physics::setVelocityCap(float cap)
{
	m_velcap = cap;
}

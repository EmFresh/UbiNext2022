#include "stdafx.h"
#include "Physics.h"
#include "GameObject.h"

using util::Vec3;
using util::GameObject;
using util::Transformer;

void Physics::awake()
{
	m_force = Vec3(0);
}

void Physics::lateUpdate(float dt)
{
	getGameObject().getComponent<Transformer>()->translateBy(m_force * dt);
	m_force = Vec3(0);
}

void Physics::addForce(util::Vec3 force)
{
	m_force += force;
}

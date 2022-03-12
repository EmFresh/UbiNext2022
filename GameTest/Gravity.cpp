#include "stdafx.h"
#include "Gravity.h"
#include "GameObject.h"
#include "Physics.h"

using util::Vec3;
using util::GameObject;


util::Vec3 m_worldGravity;

void Gravity::awake()
{}

void Gravity::update(float dt)
{
	//apply world gravity
	Physics* myPhysics = getGameObject().getComponent<Physics>();
	if(myPhysics)
		myPhysics->addForce(m_worldGravity);
	auto gravities = Component::getComponents<Gravity>();

	//apply individual object gravity
	for(auto gravity : gravities)
		if(myPhysics && gravity->getGameObject().isActive())
			myPhysics->addForce(((Gravity*)gravity)->m_gravPull * dt);


}

void Gravity::setPullForce(float force)
{
	m_gravPull = force;
}

void Gravity::setWorldGravity(util::Vec3 force)
{
	m_worldGravity = force;
}


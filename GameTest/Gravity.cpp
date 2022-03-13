#include "stdafx.h"
#include "Gravity.h"
#include "GameObject.h"
#include "Physics.h"


using util::Vec3;
using util::Vec4;
using util::GameObject;
using util::Transformer;


util::Vec3 m_worldGravity;

Gravity::Gravity():Transformer()
{}

Gravity::Gravity(const Gravity& reff) : Transformer(reff)
{}

void Gravity::awake()
{
	setParent(getGameObject()->getComponent<Transformer>());
}

void Gravity::update(float dt)
{
	if(!getGameObject()->isActive())return;

	//apply world gravity
	Physics* myPhysics = getGameObject()->getComponent<Physics>();
	if(myPhysics)
		myPhysics->addForce(m_worldGravity);
	auto gravities = Component::getComponents<Gravity>();

	//apply individual object gravity
	for(auto gravity : gravities)
		if(myPhysics && gravity->getGameObject()->isActive())
		{
			Transformer* trans1 = getGameObject()->getComponent<Transformer>(), * trans2 = gravity->getGameObject()->getComponent<Transformer>();
			myPhysics->addForce(((Gravity*)gravity)->m_gravPull /
				Vec4::distance(trans1->getWorldTranslationMatrix() * trans1->getLocalPosition(),
					trans2->getWorldTranslationMatrix() * trans2->getLocalPosition()) * dt);
		}

}

void Gravity::setPullForce(float force)
{
	m_gravPull = force;
}

void Gravity::setWorldGravity(util::Vec3 force)
{
	m_worldGravity = force;
}


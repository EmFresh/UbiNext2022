#include "stdafx.h"
#include "Player.h"
#include "App/app.h"
#include "GameObject.h"
#include "Physics.h"
#include "Bullet.h"

using util::GameObject;
using util::Transformer;
using util::Vec4;
using util::Vec3;
using util::Vec2;


void Player::awake()
{
	reffBullet= new GameObject();
	reffBullet->addComponent<Bullet>();

	m_bulletPool = util::ObjectPool(10, reffBullet);
}

void Player::update(float dt)
{
	auto& controller = App::GetController();
	auto physics = getGameObject()->getComponent<Physics>();
	auto trans = getGameObject()->getComponent<Transformer>();

	auto rot = trans->getWorldRotationMatrix() * (trans->getLocalRotationMatrix() * Vec4(0, 1, 0, 1));
	rot[3] = 0;
	rot.normalize();
	m_lookAt = Vec2{controller.GetLeftThumbStickX(), controller.GetLeftThumbStickY()};

	//rotate ship
	trans->rotate(0, 0, (float)radtodeg((double)atan2(m_lookAt.x, m_lookAt.y)));

	//apply thrust
	if(controller.GetLeftTrigger() > .2f)
	{
		physics->addForce(trans->getUp() * controller.GetLeftTrigger() * m_drive);
		m_fuel -= controller.GetLeftTrigger() * m_drive * 15;
	}
	//fire gun
	if(controller.GetRightTrigger() > .2f)
	{
		auto obj=m_bulletPool.getNewObject();
		auto bullet = obj->getComponent<Bullet>();
		auto tmpTrans= obj->getComponent<Transformer>();
		tmpTrans->translate(trans->getLocalPosition());
		bullet->setDirection(trans->getUp());
		bullet->setSpeed(.1f);
	}

	///bullet update
	for(auto bullet : m_bulletPool.getObjectList())
		bullet->update(dt);

	//IM GONNA CRASH!!! (Gravitar hath killed my game)
	if(m_fuel <= 0)
		exit(0);

}

void Player::setDriveForce(float force)
{
	m_drive = force;
}

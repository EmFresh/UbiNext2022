#pragma once
#include "Component.h"
#include "ObjectPool.h"

class Player :
	public util::Component
{
public:

	~Player() { delete reffBullet; }
	void awake();
	void update(float);

	void setDriveForce(float);
	float getFuel() { return m_fuel; }

	util::ObjectPool& getBulletPool() { return m_bulletPool; }
private:

	util::ObjectPool m_bulletPool;
	util::Vec2 m_lookAt = {};
	util::GameObject *reffBullet = nullptr;
	float m_drive = 0;
	int m_lives = 5;
	float m_fuel = 9000;
	float gunCount=0;
};


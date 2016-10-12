#pragma once
#include "cocos2d.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "AbstractWeapon.h"

using namespace cocos2d;

class RangeWeapon : public AbstractWeapon
{
public:
	RangeWeapon(const WeaponType& weaponType, const BulletType& bulletType = BulletType::STANDARD_BULLET) : 
		AbstractWeapon( weaponType ),
		bulletType (bulletType)
	{
		damageRate = 0.10f;
	};
	void triggerAttack() override;

private:
	void spawnBullet();
	Vec2 getBulletSpawnOffset(); // Calculates vector from owner's center to where bullets spawn
	BulletType bulletType;
	BulletFactory bulletFactory;
	const float bulletSpeed = 40.f;
};
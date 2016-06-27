#pragma once
#include "cocos2d.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "AbstractWeapon.h"
#include "WeaponFactory.h"

using namespace cocos2d;

class RangeWeapon : public AbstractWeapon
{
public:
	RangeWeapon(const WeaponType& weaponType, const BulletType& bulletType = BulletType::STANDARD_BULLET) : 
		AbstractWeapon( weaponType ),
		bulletType (bulletType)
	{};
	void triggerAttack() override;

private:
	void spawnBullet();
	Vec2 getBulletSpawnOffset();
	BulletType bulletType;
	BulletFactory bulletFactory;
};
#pragma once
#include "cocos2d.h"
#include "BulletFactory.h"
#include "Bullet.h"

using namespace cocos2d;

class Weapon : public Node
{
public:
	Weapon(const BulletType& bulletType = BulletType::STANDARD_BULLET) : 
		bulletType(bulletType) {};
	virtual ~Weapon();
	virtual bool init();
	virtual void fire();
	void update(float) override;
	void startFire();
	void stopFire();
	CREATE_FUNC(Weapon)

private:
	void resetCooldown();
	void reduceCooldown(float);
	void spawnBullet();
	Vec2 getBulletSpawnOffset();
	bool isFiring = false;
	float fireRate = 0.05f;
	float fireCooldown = 0;
	BulletType bulletType;
	BulletFactory bulletFactory;
};
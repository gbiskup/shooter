#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Weapon : public Node
{
public:
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
	bool isFiring = false;
	float fireRate = 0.05f;
	float fireCooldown = 0;
};
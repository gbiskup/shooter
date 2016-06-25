#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Weapon : public Node
{
public:
	virtual bool init();
	void update(float) override;
	void startFire();
	void stopFire();
	CREATE_FUNC(Weapon)
private:
	bool isFiring = false;
	float fireRate = 1.f;
	float fireCooldown = 0;
};
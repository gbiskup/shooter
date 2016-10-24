#pragma once

#include "Bullet.h"

// TODO: Add pooling
class BulletFactory
{
public:
	Bullet* createBulletOfType(const BulletType&);

private:
	Bullet* createStandardBullet();
};
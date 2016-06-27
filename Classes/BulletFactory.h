#pragma once

#include "Bullet.h"

class BulletFactory
{
public:
	Bullet* createBulletOfType(const BulletType&, Vec2, Vec2);

private:
	Bullet* createStandardBullet(Vec2, Vec2);
};
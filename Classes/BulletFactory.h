#pragma once

#include "Bullet.h"

class BulletFactory
{
public:
	Bullet* createBulletOfType(const BulletType&, const Vec2&);

private:
	Bullet* createStandardBullet(const Vec2&);
	Bullet* createBullet(const Vec2&);
};
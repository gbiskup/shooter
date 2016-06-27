#include "BulletFactory.h"
#include "CollisionBitMasks.h"

Bullet * BulletFactory::createBulletOfType(const BulletType& bulletType, Vec2 position, Vec2 offset)
{
	Bullet * bullet;
	switch (bulletType)
	{
	default:
	case BulletType::STANDARD_BULLET:
		bullet = createStandardBullet( position, offset );
		break;
	}
	return bullet;
}

Bullet * BulletFactory::createStandardBullet(Vec2 position, Vec2 offset)
{
	const int bulletSize = 5;
	const int damage = 1;
	auto bullet = Bullet::create();
	auto body = PhysicsBody::createCircle(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	body->setCategoryBitmask(static_cast<int>(CollisionBitmasks::BULLET));
	body->setCollisionBitmask(static_cast<int>(CollisionBitmasks::MONSTER) | static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));
	body->setContactTestBitmask(static_cast <int>(CollisionBitmasks::MONSTER) | static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));
	bullet->setPhysicsBody(body);
	position.add(offset);
	offset.normalize();
	offset.scale(bulletSize);
	position.add(offset);
	bullet->setPosition(position);
	bullet->setDamage(damage);
	return bullet;
}
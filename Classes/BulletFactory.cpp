#include "BulletFactory.h"
#include "CollisionBitMasks.h"
#include "AssetConstants.h"

Bullet * BulletFactory::createBulletOfType(const BulletType& bulletType)
{
	Bullet * bullet;
	switch (bulletType)
	{
	default:
	case BulletType::STANDARD_BULLET:
		bullet = createStandardBullet();
		break;
	}
	return bullet;
}

Bullet * BulletFactory::createStandardBullet()
{
	const int bulletSize = 5;
	auto bullet = Bullet::create();
	auto body = PhysicsBody::createCircle(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));

	body->setCategoryBitmask(static_cast<int>(CollisionBitmasks::BULLET));
	body->setCollisionBitmask(static_cast<int>(CollisionBitmasks::MONSTER) | static_cast<int>(CollisionBitmasks::WORLD_BOUNDS)); // Monsters can't shoot atm, skip hero collision
	body->setContactTestBitmask(static_cast <int>(CollisionBitmasks::MONSTER) | static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));

	bullet->setPhysicsBody(body);

	bullet->setDamage(5);
	auto sprite = Sprite::create(SpritePaths::BULLET); // TODO: Use spritesheet
	bullet->addChild(sprite);
	return bullet;
}
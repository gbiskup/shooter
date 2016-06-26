#include "BulletFactory.h"
#include "CollisionBitMasks.h"

Bullet * BulletFactory::createBulletOfType(const BulletType& bulletType, const Vec2& position)
{
	Bullet * bullet;
	switch (bulletType)
	{
	case BulletType::STANDARD_BULLET:
		bullet = createStandardBullet( position );
		break;

	default:
		bullet = createBullet(position);
		break;
	}
	return bullet;
}

Bullet * BulletFactory::createStandardBullet(const Vec2& position)
{
	auto bullet = createBullet( position );
	bullet->setDamage( 1 );
	return bullet;
}

Bullet * BulletFactory::createBullet(const Vec2& position)
{
	auto bullet = Bullet::create();
	auto body = PhysicsBody::createCircle( 5, PhysicsMaterial( 0.0f, 1.0f, 0.0f ));
	body->setCategoryBitmask( static_cast<int>(CollisionBitmasks::BULLET));
	body->setCollisionBitmask( static_cast<int>(CollisionBitmasks::MONSTER) | static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));
	body->setContactTestBitmask( static_cast <int>( CollisionBitmasks::MONSTER ) | static_cast<int>( CollisionBitmasks::WORLD_BOUNDS ));
	bullet->setPhysicsBody(body);
	bullet->setPosition( position );
	return bullet;
}
#include "Weapon.h"
#include "Bullet.h"

Weapon::~Weapon()
{
	log("Weapon destroyed");
}

bool Weapon::init()
{
	if (!Node::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void Weapon::update(float dt)
{
	reduceCooldown(dt);
	if (isFiring && fireCooldown <= 0.f)
	{
		fire();
		resetCooldown();
	}
}

void Weapon::resetCooldown()
{
	fireCooldown = fireRate;
}

void Weapon::fire()
{
	spawnBullet();
}

void Weapon::reduceCooldown(float dt)
{
	fireCooldown -= dt;
	if (fireCooldown < 0.f)
	{
		fireCooldown = 0.f;
	}
}

Vec2 Weapon::getBulletSpawnOffset()
{
	auto parentSize = dynamic_cast<PhysicsShapeCircle*>(getParent()->getPhysicsBody()->getShape(0));
	auto parentAngle = getParent()->getRotation();
	Vec2 offset(-(parentSize->getRadius() + 5), 0);
	offset = offset.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(parentAngle));
	return offset;
}

void Weapon::spawnBullet()
{
	auto spawnOffset = getBulletSpawnOffset();
	auto spawnPosition = getParent()->getPosition();
	spawnPosition.add( spawnOffset );
	auto bullet = bulletFactory.createBulletOfType( bulletType, spawnPosition );
	
	getParent()->getParent()->addChild(bullet);
	spawnOffset.scale(30);
	bullet->getPhysicsBody()->applyImpulse(spawnOffset);
}

void Weapon::startFire()
{
	isFiring = true;
}

void Weapon::stopFire()
{
	isFiring = false;
}


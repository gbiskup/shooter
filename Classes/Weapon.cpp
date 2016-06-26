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
	log("Boom!");
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

void Weapon::spawnBullet()
{
	auto bullet = Bullet::create();
	bullet->setPhysicsBody(PhysicsBody::createCircle(5, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	auto spawnPosition = getParent()->getPosition();
	auto parentSize = dynamic_cast<PhysicsShapeCircle*>(getParent()->getPhysicsBody()->getShape(0));
	auto parentAngle = getParent()->getRotation();
	Vec2 offset(-(parentSize->getRadius() + 5), 0);
	offset = offset.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(parentAngle));
	log("%f spawn vector: %f %f", parentAngle, spawnPosition.x, spawnPosition.y);
	spawnPosition.add(offset);
	bullet->setPosition(spawnPosition);
	getParent()->getParent()->addChild(bullet);
	offset.scale(30);
	bullet->getPhysicsBody()->applyImpulse(offset);
}

void Weapon::startFire()
{
	isFiring = true;
}

void Weapon::stopFire()
{
	isFiring = false;
}


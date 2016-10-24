#include "RangeWeapon.h"
#include "Bullet.h"

void RangeWeapon::triggerAttack()
{
	spawnBullet();
}

Vec2 RangeWeapon::getBulletSpawnOffset()
{
	auto parentShape = dynamic_cast<PhysicsShapeCircle*>(getParent()->getPhysicsBody()->getShape(0));
	auto parentAngle = getParent()->getRotation();
	Vec2 offset(parentShape->getRadius(), -15);
	offset = offset.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(parentAngle));
	return offset;
}

void RangeWeapon::spawnBullet()
{
	auto spawnPosition = getParent()->getPosition();
	//spawnPosition.y -= 10;
	auto spawnOffset = getBulletSpawnOffset();
	auto bullet = bulletFactory.createBulletOfType(bulletType);
	bullet->setPosition(spawnPosition + spawnOffset);

	bullet->setRotation(getParent()->getRotation());
	getParent()->getParent()->addChild(bullet, getParent()->getZOrder() - 1);
	
	// Spawn offset is also bullet's trajectory direction
	spawnOffset.set(1.f, 0.f);
	spawnOffset.scale(bulletSpeed);
	spawnOffset = spawnOffset.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(getParent()->getRotation()));
	bullet->getPhysicsBody()->setVelocity(spawnOffset);
}
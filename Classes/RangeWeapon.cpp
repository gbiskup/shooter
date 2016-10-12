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
	Vec2 offset(parentShape->getRadius(), 0);
	offset = offset.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(parentAngle));
	return offset;
}

void RangeWeapon::spawnBullet()
{
	auto spawnPosition = getParent()->getPosition();
	auto spawnOffset = getBulletSpawnOffset();
	auto bullet = bulletFactory.createBulletOfType( bulletType, spawnPosition, spawnOffset );
	
	bullet->setRotation(getParent()->getRotation());
	getParent()->getParent()->addChild(bullet);
	
	// Spawn offset is also bullet's trajectory direction
	spawnOffset.scale(bulletSpeed); 
	bullet->getPhysicsBody()->setVelocity(spawnOffset);
}
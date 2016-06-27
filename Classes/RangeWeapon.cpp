#include "RangeWeapon.h"
#include "Bullet.h"

void RangeWeapon::triggerAttack()
{
	spawnBullet();
}

Vec2 RangeWeapon::getBulletSpawnOffset()
{
	auto parentSize = dynamic_cast<PhysicsShapeCircle*>(getParent()->getPhysicsBody()->getShape(0));
	auto parentAngle = getParent()->getRotation();
	Vec2 offset(-parentSize->getRadius(), 0);
	offset = offset.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(parentAngle));
	return offset;
}

void RangeWeapon::spawnBullet()
{
	auto spawnOffset = getBulletSpawnOffset();
	auto spawnPosition = getParent()->getPosition();
	auto bullet = bulletFactory.createBulletOfType( bulletType, spawnPosition, spawnOffset );
	
	getParent()->getParent()->addChild(bullet);
	spawnOffset.scale(30);
	bullet->getPhysicsBody()->applyImpulse(spawnOffset);
}
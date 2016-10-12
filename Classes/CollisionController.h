#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "GameActor.h"

using namespace cocos2d;

class CollisionController
{
public:
	bool onCollisionBegin(PhysicsContact& contact);
	bool onCollisionEnded(PhysicsContact& contact);

private:
	PhysicsContactData const* contactData;
	bool handleBulletCollision(PhysicsBody*, PhysicsBody*);
	void damageActorWithBullet(const Bullet*, GameActor*);
	bool handleActorCollision(PhysicsBody*, PhysicsBody*, bool);
	bool handleMelleeAttackStart(GameActor*, GameActor*);
	bool handleMelleeAttackStop(GameActor*, GameActor*);
};
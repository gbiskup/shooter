#include "CollisionController.h"
#include "CollisionBitMasks.h"

bool CollisionController::onCollisionBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	if (!handleBulletCollision(bodyA, bodyB))
	{
		handleActorCollision(bodyA, bodyB, true);
	}
	return true;
}

bool CollisionController::onCollisionEnded(PhysicsContact & contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	handleActorCollision(bodyA, bodyB, false);
	return true;
}

bool CollisionController::handleBulletCollision(PhysicsBody *bodyA, PhysicsBody *bodyB)
{
	auto bullet = dynamic_cast<Bullet*>(bodyA->getNode());
	if (bullet != nullptr)
	{
		auto actor = dynamic_cast<GameActor*>(bodyB->getNode());
		if (actor != nullptr)
		{
			damageActorWithBullet(bullet, actor);
		}
		bullet->removeFromParent();
		return true;
	}
	else
	{
		auto bullet = dynamic_cast<Bullet*>(bodyB->getNode());
		if (bullet != nullptr)
		{
			auto actor = dynamic_cast<GameActor*>(bodyA->getNode());
			if (actor != nullptr)
			{
				damageActorWithBullet(bullet, actor);
			}
			bullet->removeFromParent();
			return true;
		}
	}
	return false;
}

void CollisionController::damageActorWithBullet(const Bullet * bullet, GameActor* actor)
{
	actor->doDamage(bullet->getDamage());
}

bool CollisionController::handleActorCollision(PhysicsBody * bodyA, PhysicsBody * bodyB, bool bodiesAreInContact)
{
	auto actorA = dynamic_cast<GameActor*>(bodyA->getNode());
	auto actorB = dynamic_cast<GameActor*>(bodyB->getNode());
	if (actorA != nullptr && actorB != nullptr)
	{
		if (bodiesAreInContact)
		{
			log("Monster Attacks!!!");
		}
		else
		{
			log("Monster stops Attack!!!");
		}
		return true;
	}
	return false;
}
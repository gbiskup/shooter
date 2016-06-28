#include "CollisionController.h"
#include "CollisionBitMasks.h"

bool CollisionController::onCollisionBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	if (!handleBulletCollision(bodyA, bodyB) && !handleBulletCollision(bodyB, bodyA))
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
		// The first body is a bullet..
		auto actor = dynamic_cast<GameActor*>(bodyB->getNode());
		if (actor != nullptr)
		{
			// ..and the second is an actor. Do damage.
			damageActorWithBullet(bullet, actor);
		}
		// TODO: don't remove piercing bullets
		bullet->removeFromParent();
		return true;
	}
	return false;
}

void CollisionController::damageActorWithBullet(const Bullet * bullet, GameActor* actor)
{
	// TODO: Decrease damage for piercing bullets
	actor->takeDamage(bullet->getDamage());
}

bool CollisionController::handleActorCollision(PhysicsBody * bodyA, PhysicsBody * bodyB, bool bodiesAreInContact)
{
	auto actorA = dynamic_cast<GameActor*>(bodyA->getNode());
	auto actorB = dynamic_cast<GameActor*>(bodyB->getNode());
	if (actorA != nullptr && actorB != nullptr)
	{
		if (bodiesAreInContact)
		{
			// Currently only monsters can have melee weapon so it has to check both directions
			if (!handleMelleeAttackStart(actorA, actorB)) // was actorA a monster?
			{
				handleMelleeAttackStart(actorB, actorA); // try actorB then..
			}
		}
		else
		{
			// Separate bodies
			if (!handleMelleeAttackStop(actorA, actorB))
			{
				handleMelleeAttackStop(actorB, actorA);
			}
		}
		return true;
	}
	return false;
}

bool CollisionController::handleMelleeAttackStart(GameActor * actorA, GameActor * actorB)
{
	if (actorA->getType() == ActorType::MONSTER && actorB->getType() == ActorType::HERO)
	{
		actorA->actionsController.startAction(ActorActionType::ATTACK);
		return true;
	}
	return false;
}

bool CollisionController::handleMelleeAttackStop(GameActor * actorA, GameActor * actorB)
{
	if (actorA->getType() == ActorType::MONSTER && actorB->getType() == ActorType::HERO)
	{
		actorA->actionsController.stopAction(ActorActionType::ATTACK);
		return true;
	}
	return false;
}

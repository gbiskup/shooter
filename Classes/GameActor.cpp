#include "GameActor.h"
#include "CollisionBitMasks.h"

bool GameActor::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

void GameActor::takeWeapon(AbstractWeapon * weaponToUse)
{
	if (weapon != nullptr)
	{
		stopAttack();
	}
	weapon = weaponToUse;
	if (weapon != nullptr)
	{
		addChild(weapon);
	}
}

void GameActor::lookAt(const Vec2 & lookAtPoint)
{
	this->lookAtPoint = lookAtPoint;
}

void GameActor::heal( int healthPoints )
{
	assert( healthPoints > 0 );
	health += healthPoints;
}

void GameActor::takeDamage( int damagePoints )
{
	assert( damagePoints > 0 );
	health -= damagePoints;
	if (health <= 0)
	{
		die();
	}
}

void GameActor::die()
{
	dead = true;
	stayIdle();
	getPhysicsBody()->setCategoryBitmask(static_cast<int>(CollisionBitmasks::DEAD_BODY));
	getPhysicsBody()->setCollisionBitmask(static_cast<int>(CollisionBitmasks::NONE));
}

void GameActor::stayIdle()
{
	actionsController.startAction(ActorActionType::IDLE);
	unscheduleUpdate();
	getPhysicsBody()->setVelocity(Vec2::ZERO);
}

void GameActor::update( float dt )
{
	desiredVelocity.setZero();
	if (!actionsController.isActionActive(ActorActionType::IDLE))
	{
		updateMoveDirection();
		applyVelocity();
		updateAngle();
		updateAttack(dt);
	}
	actionsController.clearDirtyFlags();
}

void GameActor::updateAngle()
{
	auto position = getPosition();
	position.subtract(lookAtPoint);
	setRotation( -CC_RADIANS_TO_DEGREES( position.getAngle() ));
}

void GameActor::startAttack()
{
	weapon->startAttack();
}

void GameActor::stopAttack()
{
	weapon->stopAttack();
}

void GameActor::updateAttack( float dt )
{
	if (weapon != nullptr)
	{
		if (actionsController.didActionChange(ActorActionType::ATTACK))
		{
			if (actionsController.isActionActive(ActorActionType::ATTACK))
			{
				startAttack();
			}
			else
			{
				stopAttack();
			}
		}
	}
}

void GameActor::updateMoveDirection()
{
	if (actionsController.isActionActive( ActorActionType::MOVE_UP ))
	{
		desiredVelocity.y += maxSpeed;
	}
	if (actionsController.isActionActive( ActorActionType::MOVE_DOWN ))
	{
		desiredVelocity.y -= maxSpeed;
	}
	if (actionsController.isActionActive( ActorActionType::MOVE_LEFT ))
	{
		desiredVelocity.x -= maxSpeed;
	}
	if (actionsController.isActionActive( ActorActionType::MOVE_RIGHT ))
	{
		desiredVelocity.x += maxSpeed;
	}
}

void GameActor::applyVelocity()
{
	desiredVelocity.normalize();
	desiredVelocity.scale( maxSpeed );
	
	auto body = getPhysicsBody();
	auto currentVelocity = body->getVelocity();
	auto dV = Vec2( desiredVelocity.x - currentVelocity.x, desiredVelocity.y - currentVelocity.y );

	if (lockMoveDirectionAtLookPoint)
	{
		desiredVelocity = desiredVelocity.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(getRotation() - 90));
	}

	getPhysicsBody()->setVelocity(desiredVelocity);
}

#include "GameActor.h"
#include "CollisionBitMasks.h"
#include "ActorConfig.h"

GameActor::GameActor(const ActorConfig & config):
	config(config)
{
}

const ActorType & GameActor::getType() const
{
	return config.getType();
}

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
		// Stop using an old weapon if you have any
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
	// Prevent all collisions
	getPhysicsBody()->setCategoryBitmask(static_cast<int>(CollisionBitmasks::DEAD_BODY));
	getPhysicsBody()->setCollisionBitmask(static_cast<int>(CollisionBitmasks::NONE));
}

void GameActor::stayIdle()
{
	if (weapon != nullptr)
	{
		weapon->stopAttack();
	}
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
		updateAttack();
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

void GameActor::updateAttack()
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
		desiredVelocity.y += 1.f;
	}
	if (actionsController.isActionActive( ActorActionType::MOVE_DOWN ))
	{
		desiredVelocity.y -= 1.f;
	}
	if (actionsController.isActionActive( ActorActionType::MOVE_LEFT ))
	{
		desiredVelocity.x -= 1.f;
	}
	if (actionsController.isActionActive( ActorActionType::MOVE_RIGHT ))
	{
		desiredVelocity.x += 1.f;
	}
}

void GameActor::applyVelocity()
{
	// Prevent extra speed on diagonal directions
	desiredVelocity.normalize();
	desiredVelocity.scale(maxSpeed);
	
	auto body = getPhysicsBody();
	auto currentVelocity = body->getVelocity();
	auto dV = Vec2( desiredVelocity.x - currentVelocity.x, desiredVelocity.y - currentVelocity.y );

	if (lockMoveDirectionAtLookPoint)
	{
		desiredVelocity = desiredVelocity.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(getRotation() - 90));
	}
	getPhysicsBody()->setVelocity(desiredVelocity);
}

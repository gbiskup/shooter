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
		// Stop using the old weapon if you have any
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

void GameActor::showWound(const Vec2 position)
{
	ParticleSystemQuad* blood = ParticleSystemQuad::create("particles/SplatterBlood.plist");
	blood->setScale(3.5f/getScale());
	blood->setRotation(180);
	blood->setPosition(convertToNodeSpace(position));
	addChild(blood);
}

void GameActor::lockMovement(bool lock)
{
	lockMoveDirectionAtLookPoint = lock;
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
	moveDirection = lookAtPoint;
	moveDirection.subtract(getPosition());
	setRotation(-CC_RADIANS_TO_DEGREES(moveDirection.getAngle()));
	CCLOG("rotation %f", CC_RADIANS_TO_DEGREES(moveDirection.getAngle()));
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
	if (lockMoveDirectionAtLookPoint)
	{
		// Rotate movement vector 90 degrees right, + angle between lookAtPoint and x axis so moving up will move in direction of looking (actor with 0 degrees rotation faces right)
		desiredVelocity = desiredVelocity.rotateByAngle(Vec2::ZERO, moveDirection.getAngle() + CC_DEGREES_TO_RADIANS(-90));
	}
	getPhysicsBody()->setVelocity(desiredVelocity);
}

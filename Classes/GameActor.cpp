#include "GameActor.h"

bool GameActor::init()
{
	if (!Node::init())
	{
		return false;
	}
	initActionsController();
	this->scheduleUpdate();
	return true;
}

void GameActor::initActionsController()
{
	actionsController.addActionState( ActorActionType::ATTACK );
	actionsController.addActionState( ActorActionType::MOVE_DOWN );
	actionsController.addActionState( ActorActionType::MOVE_LEFT );
	actionsController.addActionState( ActorActionType::MOVE_RIGHT );
	actionsController.addActionState( ActorActionType::MOVE_UP );
}

void GameActor::takeWeapon(Weapon * weaponToUse)
{
	weapon = weaponToUse;
	addChild(weapon);
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

void GameActor::doDamage( int damagePoints )
{
	assert( damagePoints > 0 );
	health -= damagePoints;
	log("Received damage, remaining hp: %d", health);
	if (health <= 0)
	{
		log("Actor is dead");
	}
}

void GameActor::update( float dt )
{
	desiredVelocity.setZero();
	updateMoveDirection();
	applyVelocity();
	updateAngle();
	updateAttack(dt);
	actionsController.clearDirtyFlags();
}

void GameActor::updateAngle()
{
	auto position = getPosition();
	position.subtract(lookAtPoint);
	setRotation( -CC_RADIANS_TO_DEGREES( position.getAngle() ));
}

void GameActor::updateAttack( float dt )
{
	if (weapon != nullptr)
	{
		ActionState* attackAction = actionsController.getActionState( ActorActionType::ATTACK );
		if (attackAction->didChange)
		{
			if (attackAction->isOn)
			{
				weapon->startFire();
			}
			else
			{
				weapon->stopFire();
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

	if (lockMovementAtLookPoint)
	{
		desiredVelocity = desiredVelocity.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(getRotation() - 90));
	}

	//auto force = Vec2( body->getMass() * dV );
	//desiredVelocity.y *= body->getMass();*/
	//getPhysicsBody()->setVelocity(moveDirection);
	//body->applyForce(force);
	//getPhysicsBody()->applyImpulse(force);

	getPhysicsBody()->setVelocity(desiredVelocity);
}

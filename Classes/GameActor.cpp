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
	actionsController.addActionState(ActionType::ATTACK);
	actionsController.addActionState(ActionType::MOVE_DOWN);
	actionsController.addActionState(ActionType::MOVE_LEFT);
	actionsController.addActionState(ActionType::MOVE_RIGHT);
	actionsController.addActionState(ActionType::MOVE_UP);
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

void GameActor::update(float dt)
{
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
	setRotation(-CC_RADIANS_TO_DEGREES(position.getAngle()));
}

void GameActor::updateAttack(float dt)
{
	if (weapon != nullptr)
	{
		ActionState* attackAction = actionsController.getActionState(ActionType::ATTACK);
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
	moveDirection.setZero();
	if (actionsController.isActionActive(ActionType::MOVE_UP))
	{
		moveDirection.y += moveSpeed;
	}
	if (actionsController.isActionActive(ActionType::MOVE_DOWN))
	{
		moveDirection.y -= moveSpeed;
	}
	if (actionsController.isActionActive(ActionType::MOVE_LEFT))
	{
		moveDirection.x -= moveSpeed;
	}
	if (actionsController.isActionActive(ActionType::MOVE_RIGHT))
	{
		moveDirection.x += moveSpeed;
	}
}

void GameActor::applyVelocity()
{
	moveDirection.normalize();
	moveDirection.scale(moveSpeed);
	getPhysicsBody()->setVelocity(moveDirection);
}

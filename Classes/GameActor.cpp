#include "GameActor.h"

bool GameActor::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

void GameActor::pickUpWeapon(Weapon * weaponToUse)
{
	weapon = weaponToUse;
}

void GameActor::update(float dt)
{
	updateMoveDirection();
	applyVelocity();
	updateAttack(dt);
}

void GameActor::updateAttack(float dt)
{
	/*if (weapon != nullptractionsController.isActionOn(ActionType::ATTACK))
	{
		weapon->pullTrigger();
	}*/
}

void GameActor::updateMoveDirection()
{
	moveDirection.setZero();
	if (actionsController.isActionOn(ActionType::MOVE_UP))
	{
		moveDirection.y += moveSpeed;
	}
	if (actionsController.isActionOn(ActionType::MOVE_DOWN))
	{
		moveDirection.y -= moveSpeed;
	}
	if (actionsController.isActionOn(ActionType::MOVE_LEFT))
	{
		moveDirection.x -= moveSpeed;
	}
	if (actionsController.isActionOn(ActionType::MOVE_RIGHT))
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

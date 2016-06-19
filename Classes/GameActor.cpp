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

void GameActor::update(float delta)
{
	updateMovement();
	applyMovement();
}

void GameActor::updateMovement()
{
	moveDirection.setZero();
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_UP))
	{
		moveDirection.y += moveSpeed;
	}
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_DOWN))
	{
		moveDirection.y -= moveSpeed;
	}
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_LEFT))
	{
		moveDirection.x -= moveSpeed;
	}
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_RIGHT))
	{
		moveDirection.x += moveSpeed;
	}
	moveDirection.normalize();
	moveDirection.scale(moveSpeed);
}

void GameActor::applyMovement()
{
	getPhysicsBody()->setVelocity(moveDirection);
}

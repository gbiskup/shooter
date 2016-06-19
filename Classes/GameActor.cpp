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
		moveDirection.y += 30;
	}
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_DOWN))
	{
		moveDirection.y -= 30;
	}
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_LEFT))
	{
		moveDirection.x -= 30;
	}
	if (actionsController.isActionOn(ActionsController::ActionType::MOVE_RIGHT))
	{
		moveDirection.y += 30;
	}
}

void GameActor::applyMovement()
{
	getPhysicsBody()->setVelocity(moveDirection);
}

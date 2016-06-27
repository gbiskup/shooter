#include "Monster.h"

bool Monster::init()
{
	if (!GameActor::init())
	{
		return false;
	}
	return true;
}

void Monster::update(float dt)
{
	if (target)
	{
		lookAt(target->getPosition());
	}
	GameActor::update(dt);
}

void Monster::attackTarget(const GameActor * target)
{
	this->target = target;
	lockMovementAtLookPoint = true;
	actionsController.startAction(ActorActionType::MOVE_UP);
}

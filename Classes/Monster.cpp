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
		if (target->isDead())
		{
			stayIdle();
		}
		else
		{
			lookAt(target->getPosition());
		}
	}
	GameActor::update(dt);
}

void Monster::followTarget(GameActor * target)
{
	this->target = target;
	lockMoveDirectionAtLookPoint = true;
	actionsController.startAction(ActorActionType::MOVE_UP);
}

void Monster::die()
{
	GameActor::die();
	removeFromParent();
}

void Monster::startAttack()
{
	actionsController.stopAction(ActorActionType::MOVE_UP);
	auto meleeWeapon = dynamic_cast<MeleeWeapon*>(weapon);
	if (meleeWeapon)
	{
		meleeWeapon->setTarget(target);
	}
	GameActor::startAttack();
}

void Monster::stopAttack()
{
	actionsController.startAction(ActorActionType::MOVE_UP);
	auto meleeWeapon = dynamic_cast<MeleeWeapon*>(weapon);
	if (meleeWeapon)
	{
		meleeWeapon->setTarget(nullptr);
	}
	GameActor::stopAttack();
}

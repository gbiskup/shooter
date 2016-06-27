#include <assert.h>
#include "ActionsController.h"

ActionsController::ActionsController()
{
	actions.reserve(16);
}

void ActionsController::clearDirtyFlags()
{
	for (const auto& actionState : actions)
	{
		actionState->resetDirtyFlag();
	}
}

bool ActionsController::didActionChange(const ActorActionType& actionType) const
{
	return getActionState(actionType)->getIsActive();
}

bool ActionsController::isActionActive(const ActorActionType& actionType) const
{
	return getActionState(actionType)->getIsActive();
}

void ActionsController::startAction(const ActorActionType& actionType)
{
	getActionState(actionType)->setIsActive(true);
}

void ActionsController::stopAction(const ActorActionType& actionType)
{
	getActionState(actionType)->setIsActive(false);
}

ActionState* ActionsController::getActionState(const ActorActionType& type)
{
	for (auto& actionState : actions)
	{
		if (actionState->getType() == type)
		{
			return actionState.get();
		}
	}
	return nullptr;
}

const ActionState* ActionsController::getActionState(const ActorActionType& type) const
{
	for (const auto& actionState : actions)
	{
		if (actionState->getType() == type)
		{
			return actionState.get();
		}
	}
	return nullptr;
}

void ActionsController::addActionState(const ActorActionType& type)
{
	assert(getActionState(type) == nullptr);
	actions.push_back( make_unique<ActionState>( type ));
}

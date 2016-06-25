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

bool ActionsController::didActionChange(const ActionType& actionType) const
{
	return getActionState(actionType)->getIsActive();
}

bool ActionsController::isActionActive(const ActionType& actionType) const
{
	return getActionState(actionType)->getIsActive();
}

void ActionsController::startAction(const ActionType& actionType)
{
	getActionState(actionType)->setIsActive(true);
}

void ActionsController::stopAction(const ActionType& actionType)
{
	getActionState(actionType)->setIsActive(false);
}

ActionState* ActionsController::getActionState(const ActionType& type)
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

const ActionState* ActionsController::getActionState(const ActionType& type) const
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

void ActionsController::addActionState(const ActionType& type)
{
	assert(getActionState(type) == nullptr);
	actions.push_back( make_unique<ActionState>( type ));
}

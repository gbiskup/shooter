#include <assert.h>
#include "ActionsController.h"

void ActionsController::clearDirtyFlags()
{
	for (auto& pair : currentState)
	{
		pair.second = pair.first;
	}
}

bool ActionsController::didActionChange(const ActorActionType& actionType) const
{
	auto pair = currentState[static_cast<int>(actionType)];
	return pair.first != pair.second;
}

bool ActionsController::isActionActive(const ActorActionType& actionType) const
{
	return currentState[static_cast<int>(actionType)].first;
}

void ActionsController::startAction(const ActorActionType& actionType)
{
	currentState[static_cast<int>(actionType)].first = true;
}

void ActionsController::stopAction(const ActorActionType& actionType)
{
	currentState[static_cast<int>(actionType)].first = false;
}

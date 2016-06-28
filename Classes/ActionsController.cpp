#include <assert.h>
#include "ActionsController.h"

void ActionsController::clearDirtyFlags()
{
	for (auto& pair : actionStates)
	{
		pair.second = pair.first;
	}
}

bool ActionsController::didActionChange(const ActorActionType& actionType) const
{
	auto pair = actionStates[static_cast<int>(actionType)];
	return pair.first != pair.second;
}

bool ActionsController::isActionActive(const ActorActionType& actionType) const
{
	return actionStates[static_cast<int>(actionType)].first;
}

void ActionsController::startAction(const ActorActionType& actionType)
{
	actionStates[static_cast<int>(actionType)].first = true;
}

void ActionsController::stopAction(const ActorActionType& actionType)
{
	actionStates[static_cast<int>(actionType)].first = false;
}

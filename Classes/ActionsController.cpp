#include "ActionsController.h"

bool ActionsController::isActionOn(const ActionType& actionType)
{
	auto actionToCheck = actions.find(actionType);
	if (actionToCheck != actions.end())
	{
		return actionToCheck->second > 0;
	}
	return false;
}

void ActionsController::startAction(const ActionType& actionType)
{
	auto actionToStart = actions.find(actionType);
	if (actionToStart == actions.end())
	{
		actions[actionType] = 1;
	}
	else
	{
		actionToStart->second = 1;
	}
}

void ActionsController::stopAction(const ActionType& actionType)
{
	auto actionToStop = actions.find(actionType);
	if (actionToStop != actions.end())
	{
		actionToStop->second = 0;
	}
}

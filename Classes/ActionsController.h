#pragma once
#include <vector>
#include <memory>
#include "ActionState.h"

using namespace std;

class ActionsController
{
public:
	ActionsController();
	void clearDirtyFlags();
	bool didActionChange(const ActorActionType&) const;
	bool isActionActive(const ActorActionType&) const;
	void startAction(const ActorActionType&);
	void stopAction(const ActorActionType&);
	const ActionState* getActionState(const ActorActionType&) const;
	ActionState* getActionState(const ActorActionType&);
	void addActionState(const ActorActionType&);
private:
	vector <unique_ptr<ActionState>> actions;
};

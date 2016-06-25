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
	bool didActionChange(const ActionType&) const;
	bool isActionActive(const ActionType&) const;
	void startAction(const ActionType&);
	void stopAction(const ActionType&);
	const ActionState* getActionState(const ActionType&) const;
	ActionState* getActionState(const ActionType&);
	void addActionState(const ActionType&);
private:
	vector <unique_ptr<ActionState>> actions;
};

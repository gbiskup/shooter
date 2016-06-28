#pragma once
#include <vector>

using namespace std;

enum class ActorActionType
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	ATTACK,
	IDLE
};

// This class stores actors' intentions
class ActionsController
{
public:
	ActionsController(const int maxStates = 8) : 
		actionStates(maxStates) 
	{};
	void clearDirtyFlags();
	bool didActionChange(const ActorActionType&) const;
	bool isActionActive(const ActorActionType&) const;
	void startAction(const ActorActionType&);
	void stopAction(const ActorActionType&);

private:
	vector<pair<bool, bool>> actionStates; // First bool - current state, second - previous state
};

#pragma once
#include <map>

using namespace std;

enum class ActionType
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	ATTACK
};

class ActionsController
{
public:
	bool isActionOn(const ActionType&) const;
	void startAction(const ActionType&);
	void stopAction(const ActionType&);
private:
	map <ActionType, int> actions;
};
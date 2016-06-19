#pragma once
#include <map>

using namespace std;

class ActionsController
{
public:
	enum class ActionType
	{
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		ATTACK
	};

	bool isActionOn(const ActionType&);
	void startAction(const ActionType&);
	void stopAction(const ActionType&);
private:
	map <ActionType, int> actions;
};
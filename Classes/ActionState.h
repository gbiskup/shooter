#pragma once

enum class ActionType
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	ATTACK,
	EMPTY
};

class ActionState
{
public:
	ActionState(const ActionType& actionType) : type(actionType) {}
	static const ActionState EMPTY_ACTION;
	const ActionType type;
	bool didChange = false;
	bool isOn = false;

	ActionState(const ActionState & stateToCopy) : type(stateToCopy.type), didChange(stateToCopy.didChange), isOn(stateToCopy.isOn)
	{
	}

	void setIsActive(bool isOn) 
	{ 
		this->isOn = isOn; 
		didChange = true; 
	}

	bool getIsActive() const
	{
		return isOn;
	}

	void resetDirtyFlag()
	{
		didChange = false;
	}

	const ActionType& getType() const
	{
		return type;
	}
};
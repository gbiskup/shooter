#pragma once

enum class ActorActionType
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	ATTACK,
	IDLE,
	EMPTY
};

class ActionState
{
public:
	ActionState(const ActorActionType& actionType) : type(actionType) {}
	static const ActionState EMPTY_ACTION;
	const ActorActionType type;
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

	const ActorActionType& getType() const
	{
		return type;
	}
};
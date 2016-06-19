#include "Hero.h"
#include "KeyboardController.h";

bool Hero::init()
{
	if (!GameActor::init())
	{
		return false;
	}
	keyboardController = KeyboardController::create();
	keyboardController->enable(this);
	actionsController.startAction(ActionsController::ActionType::MOVE_DOWN);
	return true;
}

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

	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_UP));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_DOWN));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_LEFT));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_RIGHT));

	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_UP));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_DOWN));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_LEFT));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_RIGHT));

	return true;
}

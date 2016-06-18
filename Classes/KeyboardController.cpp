#include "KeyboardController.h"

bool KeyboardController::init()
{
	if (!EventListenerKeyboard::init())
	{
		return false;
	}
	this->onKeyPressed = CC_CALLBACK_2(KeyboardController::handleKeyPressed, this);
	this->onKeyReleased = CC_CALLBACK_2(KeyboardController::handleKeyReleased, this);
	return true;
}

void KeyboardController::handleKeyPressed(EventKeyboard::KeyCode code, Event *event)
{
	log("Key pressed");
}

void KeyboardController::handleKeyReleased(EventKeyboard::KeyCode code, Event *event)
{
	log("Key released");
}

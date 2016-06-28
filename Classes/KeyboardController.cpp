#include "KeyboardController.h"

void KeyboardController::registerKeyDownCallback(EventKeyboard::KeyCode keyCode, function<void()> callback)
{
	keyDownToAction[keyCode] = callback;
}

void KeyboardController::registerKeyUpCallback(EventKeyboard::KeyCode keyCode, function<void()> callback)
{
	keyUpToAction[keyCode] = callback;
}

void KeyboardController::handleKeyPressed(EventKeyboard::KeyCode code, Event *event) const
{
	auto mapping = keyDownToAction.find(code);
	if (mapping != keyDownToAction.end())
	{
		event->stopPropagation();
		mapping->second();
	}
}

void KeyboardController::handleKeyReleased(EventKeyboard::KeyCode code, Event *event) const
{
	auto mapping = keyUpToAction.find(code);
	if (mapping != keyUpToAction.end())
	{
		event->stopPropagation();
		mapping->second();
	}
}
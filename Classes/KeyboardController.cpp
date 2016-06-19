#include "KeyboardController.h"
#include "GameplayScene.h"

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

void KeyboardController::enable(Node * target)
{
	target->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this, target);
}

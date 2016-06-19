#pragma once
#include <map>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class KeyboardController : private EventListenerKeyboard
{
public:
	virtual bool init();
	void registerKeyDownCallback(EventKeyboard::KeyCode, function<void()>);
	void registerKeyUpCallback(EventKeyboard::KeyCode, function<void()>);
	void KeyboardController::enable(Node * target);
	CREATE_FUNC(KeyboardController);

private:
	void handleKeyPressed(EventKeyboard::KeyCode, Event*);
	void handleKeyReleased(EventKeyboard::KeyCode, Event*);
	map <EventKeyboard::KeyCode, function<void()>> keyDownToAction;
	map <EventKeyboard::KeyCode, function<void()>> keyUpToAction;
	map <EventKeyboard::KeyCode, bool> keysDown;
};
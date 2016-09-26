#pragma once
#include <map>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

// This class stores and calls callback function mapped to key codes when keyboard events happen
class KeyboardController
{
public:
	void handleKeyPressed(EventKeyboard::KeyCode, Event*) const;
	void handleKeyReleased(EventKeyboard::KeyCode, Event*) const;
	void registerKeyDownCallback(EventKeyboard::KeyCode, function<void()>);
	void registerKeyUpCallback(EventKeyboard::KeyCode, function<void()>);

private:
	map <EventKeyboard::KeyCode, function<void()>> keyDownToAction;
	map <EventKeyboard::KeyCode, function<void()>> keyUpToAction;
};
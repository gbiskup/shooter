#pragma once
#include <map>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class KeyboardController : private EventListenerKeyboard
{
public:
	~KeyboardController();
	bool init();
	void registerKeyDownCallback(EventKeyboard::KeyCode, function<void()>);
	void registerKeyUpCallback(EventKeyboard::KeyCode, function<void()>);
	void enable(Node * target);
	void disable();
	CREATE_FUNC(KeyboardController)

private:
	void handleKeyPressed(EventKeyboard::KeyCode, Event*) const;
	void handleKeyReleased(EventKeyboard::KeyCode, Event*) const;
	map <EventKeyboard::KeyCode, function<void()>> keyDownToAction;
	map <EventKeyboard::KeyCode, function<void()>> keyUpToAction;
	map <EventKeyboard::KeyCode, bool> keysDown;
	Node* target = nullptr;
};
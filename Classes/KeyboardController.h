#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class KeyboardController : public EventListenerKeyboard
{
public:
	virtual bool init();
	void handleKeyPressed(EventKeyboard::KeyCode, Event*);
	void handleKeyReleased(EventKeyboard::KeyCode, Event *);

	CREATE_FUNC(KeyboardController);

private:
};
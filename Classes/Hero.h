#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "KeyboardController.h"

using namespace cocos2d;

class Hero : public GameActor
{
public:
	virtual bool init();
	CREATE_FUNC(Hero);

private:
	KeyboardController * keyboardController;
};
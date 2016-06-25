#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "MouseController.h"

using namespace cocos2d;

class Hero : public GameActor
{
public:
	~Hero();
	bool init();
	CREATE_FUNC(Hero)
private:

};
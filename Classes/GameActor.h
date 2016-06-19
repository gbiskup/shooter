#pragma once

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

enum class ActorType
{
	HERO,
	MONSTER
};

class GameActor : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(GameActor);
};
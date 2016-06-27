#pragma once
#include "cocos2d.h"
#include "GameActor.h"

using namespace cocos2d;

class Hero : public GameActor
{
public:
	Hero(const ActorType& actorType) : GameActor(actorType) {};
};
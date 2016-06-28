#pragma once
#include "cocos2d.h"
#include "GameActor.h"

using namespace cocos2d;

// For future use like picking up health, ammo and guns.
class Hero : public GameActor
{
public:
	Hero(const ActorType& actorType) :
		GameActor(actorType)
	{};
};
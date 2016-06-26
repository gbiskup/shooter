#pragma once

#include "cocos2d.h"
#include "GameActor.h"

using namespace cocos2d;
using namespace std;

class ActorFactory
{
public:
	GameActor * createActorOfType(const ActorType&, const Vec2&);

private:
	GameActor * createHero();
	GameActor * createMonster();
};
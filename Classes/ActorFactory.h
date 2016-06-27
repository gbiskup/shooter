#pragma once

#include "cocos2d.h"
#include "GameActor.h"
#include "Monster.h"
#include "Hero.h"

using namespace cocos2d;
using namespace std;

class ActorFactory
{
public:
	GameActor * createActorOfType(const ActorType&, const Vec2&);
	Hero * createHero(const Vec2&);
	Monster * createMonster(const Vec2&);
};
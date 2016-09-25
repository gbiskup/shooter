#pragma once

#include "cocos2d.h"
#include "GameNodeFactory.h"
#include "GameActor.h"
#include "ActorType.h"
#include "Monster.h"
#include "Hero.h"
#include "WeaponFactory.h"

using namespace cocos2d;
using namespace std;

// TODO: Add pooling
class ActorFactory : public GameNodeFactory
{
public:
	GameActor * createActorOfType(const ActorConfig&);
	Hero * createHero(const ActorConfig&);
	Monster * createMonster(const ActorConfig&);
private:
	WeaponFactory weaponFactory;
	void updateConfig(GameActor * actor, const ActorConfig & config);;
};
#pragma once

#include "cocos2d.h"
#include "AbstractWeapon.h"
#include "ActorType.h"

struct ActorConfig
{
	static ActorConfig getHeroConfig();
	static ActorConfig getMonsterConfig(const MonsterType&);
	const ActorType getType() const;
	int health;
	float speed;
	float size;
	Vec2 position;
	ActorType type;
	WeaponType weaponType;
};

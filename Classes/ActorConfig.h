#pragma once

#include "cocos2d.h"
#include "AbstractWeapon.h"
#include "ActorType.h"

class ActorConfig
{
public:
	ActorConfig(const ActorType& type) :
		type(type) 
	{};
	~ActorConfig()
	{};
	const ActorType getType() const;
	int health;
	float speed;
	Vec2 position;

private:
	const ActorType type;
	WeaponType weaponType;
};

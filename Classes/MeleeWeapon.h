#pragma once
#include "AbstractWeapon.h"
#include "GameActor.h"

class GameActor;

class MeleeWeapon : public AbstractWeapon
{
public:
	Vec2 woundPosition;
	MeleeWeapon(const WeaponType& type) : 
		AbstractWeapon(type) 
	{
		damageRate = 0.25;
	};

	// Actor to attack. Only set durring collision with weapon's owner
	void setTarget(GameActor* target) 
	{ 
		this->target = target; 
	};

	// Should be set in constructor but weapon factory needs variadic templates implementation first
	void setDamage(int damage) 
	{ 
		this->damage = damage; 
	};

protected:
	void triggerAttack() override;

private:
	GameActor* target = nullptr;
	int damage = 0;// 20;
};
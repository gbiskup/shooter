#pragma once
#include "AbstractWeapon.h"
#include "GameActor.h"

class GameActor;

class MeleeWeapon : public AbstractWeapon
{
public:
	MeleeWeapon(const WeaponType& type) : AbstractWeapon(type) {};
	void setTarget(GameActor* target) { this->target = target; };
	void setDamage(int damage) { this->damage = damage; };

protected:
	void triggerAttack() override;

private:
	GameActor* target = nullptr;
	int damage = 20;
};
#pragma once
#include "GameNodeFactory.h"
#include "AbstractWeapon.h"
#include "MeleeWeapon.h"

class WeaponFactory : public GameNodeFactory
{
public:
	AbstractWeapon * createWeapon(const WeaponType&);
	MeleeWeapon * createMeleeWeapon();
};
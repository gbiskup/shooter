#pragma once
#include "GameNodeFactory.h"
#include "AbstractWeapon.h"

class WeaponFactory : public GameNodeFactory
{
public:
	AbstractWeapon * createWeapon(const WeaponType&);
};
#include "WeaponFactory.h"
#include "MeleeWeapon.h"

AbstractWeapon * WeaponFactory::createWeapon(const WeaponType &type)
{
	auto weapon = createNode<MeleeWeapon, WeaponType>(type);
	weapon->setDamage(20);
	return weapon;
}

#include "WeaponFactory.h"
#include "MeleeWeapon.h"
#include "RangeWeapon.h"

AbstractWeapon * WeaponFactory::createWeapon(const WeaponType &type)
{
	AbstractWeapon* createdWeapon;
	switch (type)
	{
	default:
	case WeaponType::MELEE:
		createdWeapon = static_cast<AbstractWeapon*>(createMeleeWeapon());
		break;

	case WeaponType::RANGE:
		createdWeapon = static_cast<AbstractWeapon*>(createNode<RangeWeapon, WeaponType>(type));
		break;
	}
	return createdWeapon;
}

MeleeWeapon * WeaponFactory::createMeleeWeapon()
{
	auto melee = createNode<MeleeWeapon, WeaponType>(WeaponType::MELEE);
	melee->setDamage(20);
	return melee;
}

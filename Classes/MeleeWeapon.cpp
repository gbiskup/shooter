#include "MeleeWeapon.h"

void MeleeWeapon::triggerAttack()
{
	if (target != nullptr)
	{
		target->takeDamage(damage);
	}
}

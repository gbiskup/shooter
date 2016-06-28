#include "AbstractWeapon.h"

bool AbstractWeapon::init()
{
	if (!Node::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void AbstractWeapon::update(float dt)
{
	reduceCooldown(dt);
	if (isAttacking && damageCooldown <= 0.f)
	{
		triggerAttack();
		resetCooldown();
	}
}

void AbstractWeapon::resetCooldown()
{
	damageCooldown = damageRate;
}

void AbstractWeapon::reduceCooldown(float dt)
{
	damageCooldown -= dt;
	if (damageCooldown < 0.f)
	{
		damageCooldown = 0.f;
	}
}

void AbstractWeapon::startAttack()
{
	isAttacking = true;
}

void AbstractWeapon::stopAttack()
{
	isAttacking = false;
}



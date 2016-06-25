#include "Weapon.h"

Weapon::~Weapon()
{
	log("Weapon destroyed");
}

bool Weapon::init()
{
	if (!Node::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void Weapon::update(float dt)
{
	reduceCooldown(dt);
	if (isFiring && fireCooldown <= 0.f)
	{
		fire();
		resetCooldown();
	}
}

void Weapon::resetCooldown()
{
	fireCooldown = fireRate;
}

void Weapon::fire()
{
	log("Boom!");
	
}

void Weapon::reduceCooldown(float dt)
{
	fireCooldown -= dt;
	if (fireCooldown < 0.f)
	{
		fireCooldown = 0.f;
	}
}

void Weapon::startFire()
{
	isFiring = true;
}

void Weapon::stopFire()
{
	isFiring = false;
}


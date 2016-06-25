#include "Weapon.h"

bool Weapon::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void Weapon::update(float dt)
{
	if (isFiring)
	{
		log("Bang, bang");
	}
	fireCooldown -= dt;
}

void Weapon::startFire()
{
	isFiring = true;
	log("Ognia!!!");
}

void Weapon::stopFire()
{
	isFiring = false;
	log("Wstrzymac ogien");
}


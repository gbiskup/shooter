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
}

void Weapon::fire(const Vec2 &)
{
}


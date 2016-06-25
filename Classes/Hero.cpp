#include "Hero.h"

Hero::~Hero()
{
	log("Hero destroyed");
}

bool Hero::init()
{
	if (!GameActor::init())
	{
		return false;
	}
	return true;
}

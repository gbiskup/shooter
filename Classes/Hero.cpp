#include "Hero.h"

bool Hero::init()
{
	if (!GameActor::init())
	{
		return false;
	}
	return true;
}

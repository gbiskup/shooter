#pragma once
#include "cocos2d.h"

using namespace cocos2d;

// This game needs more bullet types..
enum class BulletType
{
	STANDARD_BULLET
};

class Bullet : public Node
{
public:
	// Will be used for bullets piercing through monsters
	void setDamage(int damage) 
	{ 
		this->damage = damage; 
	};

	int getDamage() const 
	{ 
		return damage; 
	};

	CREATE_FUNC(Bullet)

private:
	int damage = 0;
};
#pragma once

#include "cocos2d.h"

using namespace cocos2d;

enum class BulletType
{
	STANDARD_BULLET
};

class Bullet : public Node
{
public:
	~Bullet() { log("Bullet destroyed"); };
	void setDamage(int damage) { this->damage = damage; };
	int getDamage() const { return damage; };
	CREATE_FUNC(Bullet)

private:
	int damage = 0;
};
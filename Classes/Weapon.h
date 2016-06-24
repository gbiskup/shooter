#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Weapon : public Node
{
public:
	virtual bool init();
	void update(float) override;
	void fire(const Vec2&);
	CREATE_FUNC(Weapon)
private:
	float fireRate = 100;
};
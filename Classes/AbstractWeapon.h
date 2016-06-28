#pragma once
#include "cocos2d.h"
#include "BulletFactory.h"
#include "Bullet.h"

using namespace cocos2d;

enum class WeaponType
{
	MELEE,
	RANGE
};

class AbstractWeapon : public Node
{
public:
	AbstractWeapon(const WeaponType& type) : 
		type(type) 
	{};
	virtual ~AbstractWeapon() = default;
	virtual bool init();
	void update(float) override;
	void startAttack();
	void stopAttack();

protected:
	virtual void triggerAttack() = 0;

private:
	void resetCooldown();
	void reduceCooldown(float);
	WeaponType type;
	bool isAttacking = false;
	float damageRate = 0.25f;
	float damageCooldown = 0;
};
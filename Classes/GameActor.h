#pragma once

#include "cocos2d.h"
#include "ActionsController.h"
#include "Weapon.h"

using namespace cocos2d;
using namespace std;

enum class ActorType
{
	HERO,
	MONSTER
};

class GameActor : public Node
{
public:
	virtual bool init();
	void update(float) override;
	void takeWeapon(Weapon*);
	void lookAt(const Vec2&);
	void heal(int);
	void doDamage(int);
	ActionsController actionsController;
	CREATE_FUNC(GameActor)

protected:
	Vec2 desiredVelocity;
	Vec2 lookAtPoint;
	Weapon* weapon;
	int health;

private:
	void initActionsController();
	void updateMoveDirection();
	void applyVelocity();
	void updateAngle();
	void updateAttack(float);
	float maxSpeed = 300.f;
};
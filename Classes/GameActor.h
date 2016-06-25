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
	void pickUpWeapon(Weapon*);
	ActionsController actionsController;
	CREATE_FUNC(GameActor)

protected:
	Vec2 moveDirection;
	Vec2 lookAtPoint;
	Weapon* weapon;
private:
	float moveSpeed = 300.f;
	void updateMoveDirection();
	void applyVelocity();
	void updateAttack(float);
};
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
	GameActor(const ActorType& actorType) : type(actorType) {};
	virtual bool init();
	void update(float) override;
	void takeWeapon(Weapon*);
	void lookAt(const Vec2&);
	void heal(int);
	void doDamage(int);
	void setMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; };
	bool isDead() { return dead; };
	ActionsController actionsController;

protected:
	void die();
	Vec2 desiredVelocity;
	Vec2 lookAtPoint;
	Weapon* weapon = nullptr;
	float maxSpeed = 300.f;
	int health = 0;
	bool dead = false;
	bool lockMoveDirectionAtLookPoint = false;

private:
	const ActorType type;
	void initActionsController();
	void updateMoveDirection();
	void applyVelocity();
	void updateAngle();
	void updateAttack(float);
};
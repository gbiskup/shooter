#pragma once

#include "cocos2d.h"
#include "ActionsController.h"
#include "AbstractWeapon.h"

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
	virtual void takeWeapon(AbstractWeapon*);
	void lookAt(const Vec2&);
	void heal(int);
	void takeDamage(int);
	void setMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; };
	int getHealth() const { return health; };
	bool isDead() const { return dead; };
	const ActorType& getType() const { return type; };
	ActionsController actionsController;

protected:
	virtual void startAttack();
	virtual void stopAttack();
	virtual void die();
	void stayIdle();
	Vec2 desiredVelocity;
	Vec2 lookAtPoint;
	AbstractWeapon* weapon = nullptr;
	float maxSpeed = 300.f;
	int health = 0;
	bool dead = false;
	bool lockMoveDirectionAtLookPoint = false;

private:
	const ActorType type;
	void updateMoveDirection();
	void applyVelocity();
	void updateAngle();
	void updateAttack(float);
};
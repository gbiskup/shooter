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
	GameActor(const ActorType& actorType) :
		type(actorType)
	{};

	void setMaxSpeed(float maxSpeed) 
	{ 
		this->maxSpeed = maxSpeed;
	};

	const ActorType& getType() const 
	{ 
		return type; 
	};

	int getHealth() const 
	{ 
		return health; 
	};

	bool isDead() const 
	{ 
		return dead; 
	};

	virtual bool init();
	virtual void takeWeapon(AbstractWeapon*);
	void update(float) override;
	void lookAt(const Vec2&);
	void heal(int);
	void takeDamage(int);
	ActionsController actionsController;

protected:
	virtual void startAttack();
	virtual void stopAttack();
	virtual void die();
	void stayIdle();
	Vec2 desiredVelocity; // vector telling what direction this actor is trying to move
	Vec2 lookAtPoint;
	AbstractWeapon* weapon = nullptr;
	float maxSpeed = 300.f;
	int health = 0;
	bool dead = false;
	bool lockMoveDirectionAtLookPoint = false; // makes actor rotate it's move direction in relation to where it looks

private:
	const ActorType type;
	void updateMoveDirection();
	void applyVelocity();
	void updateAngle();
	void updateAttack();
};
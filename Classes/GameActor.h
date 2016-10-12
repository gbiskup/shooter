#pragma once

#include "cocos2d.h"
#include "ActorType.h"
#include "ActionsController.h"
#include "AbstractWeapon.h"
#include "ActorConfig.h"

using namespace cocos2d;
using namespace std;



class GameActor : public Node
{
public:
	GameActor(const ActorConfig& config);

	void setMaxSpeed(float maxSpeed) 
	{ 
		this->maxSpeed = maxSpeed;
	};

	const ActorType& getType() const;

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
	void showWound(const Vec2);
	void lockMovement(bool);
	ActionsController actionsController;

protected:
	virtual void startAttack();
	virtual void stopAttack();
	virtual void die();
	void stayIdle();
	Vec2 desiredVelocity; // vector telling what direction this actor is trying to move
	Vec2 lookAtPoint;
	Vec2 moveDirection;
	AbstractWeapon* weapon = nullptr;
	float maxSpeed = 300.f;
	int health = 0;
	bool dead = false;
	bool lockMoveDirectionAtLookPoint = false; // makes actor rotate it's move direction in relation to where it looks

private:
	ActorConfig config;
	void updateMoveDirection();
	void applyVelocity();
	void updateAngle();
	void updateAttack();
};

#pragma once

#include "cocos2d.h"
#include "ActionsController.h"

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
	CREATE_FUNC(GameActor);

protected:
	virtual void attack();
	ActionsController actionsController;
	Vec2 moveDirection;

private:
	float moveSpeed = 300.f;
	void updateMovement();
	void applyMovement();
};
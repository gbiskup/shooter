#pragma once
#include "cocos2d.h"
#include "GameActor.h"

class Monster : public GameActor
{
public:
	Monster(const ActorType& actorType) : GameActor::GameActor(actorType) {};
	bool init();
	void update(float) override;
	void attackTarget( const GameActor* );
private:
	const GameActor* target = nullptr;
};
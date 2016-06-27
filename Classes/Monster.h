#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "MeleeWeapon.h"

class Monster : public GameActor
{
public:
	Monster(const ActorType& actorType) : GameActor::GameActor(actorType) {};
	bool init();
	void update(float) override;
	void followTarget(GameActor*);
protected:
	void startAttack() override;
	void stopAttack() override;
private:
	GameActor* target = nullptr;
};
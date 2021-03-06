#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "MeleeWeapon.h"
#include "ActorConfig.h"

class Monster : public GameActor
{
public:
	Monster(const ActorConfig& config) : 
		GameActor::GameActor(config)
	{};
	bool init();
	void die() override;
	void update(float) override;
	void followTarget(GameActor*);
protected:
	void startAttack() override;
	void stopAttack() override;
private:
	GameActor* target = nullptr;
};
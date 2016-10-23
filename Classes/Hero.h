#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "ActorConfig.h"

using namespace cocos2d;

// For future use like picking up health, ammo and guns.
class Hero : public GameActor
{
public:
	Hero(const ActorConfig& config) :
		GameActor(config)
	{};
protected:
	virtual void updateAnimation() override;
	virtual void startAttack() override;
	virtual void stopAttack() override;
};
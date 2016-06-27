#pragma once
#include "cocos2d.h"
#include "GameActor.h"

class Monster : public GameActor
{
public:
	bool init();
	void update(float) override;
	void attackTarget( const GameActor* );
	CREATE_FUNC(Monster)
private:
	const GameActor* target;
};
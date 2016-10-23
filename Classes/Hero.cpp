#include "Hero.h"
#include "HeroAnimationNames.h"

void Hero::updateAnimation()
{
	if (animationName != HeroAnimationNames::SHOOT)
	{
		if (desiredVelocity.equals(Vec2::ZERO))
		{
			if (animationName != HeroAnimationNames::IDLE)
			{
				animation->setAnimation(0, HeroAnimationNames::IDLE, true);
				animationName = HeroAnimationNames::IDLE;
			}
		}
		else if (animationName != HeroAnimationNames::MOVE)
		{
			animation->setAnimation(0, HeroAnimationNames::MOVE, true);
			animationName = HeroAnimationNames::MOVE;
		}
	}
}

void Hero::startAttack()
{
	animationName = HeroAnimationNames::SHOOT;
	animation->setAnimation(0, HeroAnimationNames::SHOOT, true);
	GameActor::startAttack();
}

void Hero::stopAttack()
{
	GameActor::stopAttack();
	animationName = "";
}

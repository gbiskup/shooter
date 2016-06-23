#include "ActorFactory.h"
#include "Hero.h"

GameActor * ActorFactory::createActorOfType(ActorType actorType)
{
	GameActor * actor;
	switch (actorType)
	{
		case ActorType::HERO:
			actor = static_cast<GameActor*>( createHero() );
			break;

		default:
		case ActorType::MONSTER:
			break;
	}
	return actor;
}

GameActor * ActorFactory::createHero()
{
	auto hero = Hero::create();
	size.width = 100;
	size.height = 40;
	//hero->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	hero->setPhysicsBody(PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	hero->setPosition(Vec2(500, 500));
	return static_cast<GameActor*>(hero);
}


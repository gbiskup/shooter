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
			actor = createMonster();
			break;
	}
	return actor;
}

GameActor * ActorFactory::createMonster()
{
	auto monster = GameActor::create();
	size.width = 100;
	size.height = 40;
	monster->setPhysicsBody(PhysicsBody::createCircle(40, PhysicsMaterial(10.0f, 1.0f, 0.0f)));
	//hero->setPhysicsBody(PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	monster->setPosition(Vec2(530, 200));
	monster->takeWeapon(Weapon::create());
	return monster;
}

GameActor * ActorFactory::createHero()
{
	auto hero = Hero::create();
	size.width = 100;
	size.height = 40;
	hero->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	//hero->setPhysicsBody(PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	hero->setPosition(Vec2(500, 500));
	hero->takeWeapon(Weapon::create());
	return static_cast<GameActor*>(hero);
}


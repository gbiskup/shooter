#include "ActorFactory.h"
#include "Hero.h"
#include "CollisionBitMasks.h"

GameActor * ActorFactory::createActorOfType(const ActorType& actorType)
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
	auto body = PhysicsBody::createCircle( 40, PhysicsMaterial( 1.0f, 1.0f, 0.0f ));
	body->setCollisionBitmask( static_cast <int>( CollisionBitmasks::MONSTER ));
	body->setContactTestBitmask( static_cast <int>( CollisionBitmasks::BULLET ) | static_cast<int>( CollisionBitmasks::HERO ));
	monster->setPhysicsBody( body );
	monster->setPosition( Vec2( 530, 200 ));
	monster->takeWeapon( Weapon::create() );
	return monster;
}

GameActor * ActorFactory::createHero()
{
	auto hero = Hero::create();
	auto body = PhysicsBody::createCircle( 30, PhysicsMaterial( 1.0f, 1.0f, 0.0f ));
	body->setCollisionBitmask( static_cast<int>( CollisionBitmasks::HERO ));
	hero->setPhysicsBody( body );
	hero->setPosition( Vec2( 500, 500 ));
	hero->takeWeapon( Weapon::create() );
	return static_cast<GameActor*>( hero );
}


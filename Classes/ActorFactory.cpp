#include "ActorFactory.h"
#include "CollisionBitMasks.h"
#include "AbstractWeapon.h"
#include "AssetConstants.h"
#include "ActorConfig.h"

GameActor * ActorFactory::createActorOfType(const ActorConfig& actorConfig)
{
	GameActor * actor;
	switch (actorConfig.getType())
	{
		case ActorType::HERO:
			actor = static_cast<GameActor*>( createHero( actorConfig ));
			break;

		default:
		case ActorType::MONSTER:
			actor = static_cast<GameActor*>( createMonster( actorConfig ));
			break;
	}
	return actor;
}

Monster * ActorFactory::createMonster(const ActorConfig& config)
{
	auto body = PhysicsBody::createCircle( 40, PhysicsMaterial( 1.0f, 1.0f, 0.0f ));
	body->setCategoryBitmask( static_cast<int>( CollisionBitmasks::MONSTER ));
	body->setCollisionBitmask( 
		static_cast <int>( CollisionBitmasks::BULLET ) | 
		static_cast <int>(CollisionBitmasks::HERO) | 
		static_cast <int>(CollisionBitmasks::MONSTER)
	);
	body->setContactTestBitmask( 
		static_cast <int>( CollisionBitmasks::BULLET ) | 
		static_cast<int>(CollisionBitmasks::HERO )
	);

	auto monster = createNode<Monster, ActorConfig>(ActorConfig(ActorType::MONSTER));
	monster->setPhysicsBody( body );
	updateConfig(monster, config);
	monster->takeWeapon(weaponFactory.createWeapon(WeaponType::MELEE));
	auto sprite = Sprite::create(SpritePaths::MONSTER);
	sprite->setRotation(180);
	monster->addChild(sprite);

	return monster;
}

void ActorFactory::updateConfig(GameActor*actor, const ActorConfig & config)
{
	actor->heal(config.health);
	actor->setPosition(config.position);
	actor->setMaxSpeed(config.speed);
}

Hero* ActorFactory::createHero(const ActorConfig& config)
{
	auto body = PhysicsBody::createCircle( 30, PhysicsMaterial( 1.0f, 1.0f, 0.0f ));
	body->setCategoryBitmask( static_cast<int>( CollisionBitmasks::HERO ));
	body->setCollisionBitmask( 
		static_cast<int>( CollisionBitmasks::MONSTER ) | 
		static_cast<int>( CollisionBitmasks::WORLD_BOUNDS )
	);
	body->setContactTestBitmask( static_cast<int>( CollisionBitmasks::MONSTER ));

	auto hero = createNode<Hero, ActorConfig>(ActorType::HERO);
	hero->setPhysicsBody(body);
	hero->takeWeapon(weaponFactory.createWeapon(WeaponType::RANGE));
	updateConfig(hero, config);

	auto sprite = Sprite::create(SpritePaths::HERO);
	sprite->setRotation(180);
	sprite->setAnchorPoint(Vec2(0.5f, 0.3f));
	hero->addChild(sprite);
	return hero;
}


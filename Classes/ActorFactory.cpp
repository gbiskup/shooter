#include "ActorFactory.h"
#include "CollisionBitMasks.h"
#include "AbstractWeapon.h"
#include "AssetConstants.h"
#include "ActorConfig.h"

GameActor * ActorFactory::createActorNode(const ActorConfig& actorConfig)
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
	actor->takeWeapon( weaponFactory.createWeapon( actorConfig.weaponType ));
	return actor;
}

Monster * ActorFactory::createMonster(const ActorConfig& config)
{
	auto monster = createNode<Monster, ActorConfig>(config);
	updateConfig(monster, config);

	auto body = PhysicsBody::createCircle(config.size * 40.f, PhysicsMaterial(1.0f, 1.0f, 0.0f));
	body->setLinearDamping(0.6);
	body->setCategoryBitmask(static_cast<int>(CollisionBitmasks::MONSTER));
	body->setCollisionBitmask(
		static_cast <int>(CollisionBitmasks::BULLET) |
		static_cast <int>(CollisionBitmasks::HERO) |
		static_cast <int>(CollisionBitmasks::MONSTER)
	);
	body->setContactTestBitmask(
		static_cast <int>(CollisionBitmasks::BULLET) |
		static_cast<int>(CollisionBitmasks::HERO)
	);
	monster->setPhysicsBody( body );
	
	auto sprite = Sprite::create( SpritePaths::MONSTER );
	sprite->setRotation( 180 );
	sprite->setScale( config.size );
	monster->addChild( sprite );

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
	auto hero = createNode<Hero, ActorConfig>(config);
	updateConfig(hero, config);

	auto body = PhysicsBody::createCircle(config.size * 30.f, PhysicsMaterial(1.0f, 1.0f, 0.0f));
	body->setLinearDamping(0.6);
	body->setCategoryBitmask(static_cast<int>(CollisionBitmasks::HERO));
	body->setCollisionBitmask(
		static_cast<int>(CollisionBitmasks::MONSTER) |
		static_cast<int>(CollisionBitmasks::WORLD_BOUNDS)
	);
	body->setContactTestBitmask(static_cast<int>(CollisionBitmasks::MONSTER));
	hero->setPhysicsBody(body);

	auto sprite = Sprite::create(SpritePaths::HERO);
	sprite->setRotation(180);
	sprite->setAnchorPoint(Vec2(0.5f, 0.3f));
	sprite->setScale(config.size);
	hero->addChild(sprite);
	return hero;
}


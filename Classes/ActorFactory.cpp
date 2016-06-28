#include "ActorFactory.h"
#include "CollisionBitMasks.h"
#include "AbstractWeapon.h"
#include "AssetConstants.h"

GameActor * ActorFactory::createActorOfType(const ActorType& actorType, const Vec2& spawnPosition)
{
	GameActor * actor;
	switch (actorType)
	{
		case ActorType::HERO:
			actor = static_cast<GameActor*>( createHero( spawnPosition ));
			break;

		default:
		case ActorType::MONSTER:
			actor = static_cast<GameActor*>( createMonster( spawnPosition ));
			break;
	}
	return actor;
}

Monster * ActorFactory::createMonster(const Vec2& spawnPosition)
{
	auto body = PhysicsBody::createCircle( 40, PhysicsMaterial( 1.0f, 1.0f, 0.0f ));
	body->setCategoryBitmask( static_cast<int>( CollisionBitmasks::MONSTER ));
	body->setCollisionBitmask( static_cast <int>( CollisionBitmasks::BULLET ) | static_cast <int>(CollisionBitmasks::HERO ));
	body->setContactTestBitmask( static_cast <int>( CollisionBitmasks::BULLET ) | static_cast<int>(CollisionBitmasks::HERO ));

	auto monster = createNode<Monster, ActorType>(ActorType::MONSTER);
	monster->setPhysicsBody( body );
	monster->heal(100);
	monster->setMaxSpeed(100.f);
	monster->setPosition(spawnPosition);
	monster->takeWeapon(weaponFactory.createWeapon(WeaponType::MELEE));
	auto sprite = Sprite::create(SpritePaths::MONSTER);
	sprite->setRotation(180);
	monster->addChild(sprite);

	return monster;
}

Hero* ActorFactory::createHero(const Vec2& spawnPosition)
{
	auto body = PhysicsBody::createCircle( 30, PhysicsMaterial( 1.0f, 1.0f, 0.0f ));
	body->setCategoryBitmask( static_cast<int>( CollisionBitmasks::HERO ));
	body->setCollisionBitmask( static_cast<int>( CollisionBitmasks::MONSTER ) | static_cast<int>( CollisionBitmasks::WORLD_BOUNDS ));
	body->setContactTestBitmask( static_cast<int>( CollisionBitmasks::MONSTER ));

	auto hero = createNode<Hero, ActorType>(ActorType::HERO);
	hero->setPhysicsBody(body);
	hero->takeWeapon(weaponFactory.createWeapon(WeaponType::RANGE));
	hero->heal(100);
	hero->setPosition(spawnPosition);
	auto sprite = Sprite::create(SpritePaths::HERO);
	sprite->setRotation(180);
	sprite->setAnchorPoint(Vec2(0.5f, 0.3f));
	hero->addChild(sprite);
	return hero;
}


#include <random>
#include "ActorConfig.h"

ActorConfig ActorConfig::getHeroConfig()
{
	ActorConfig config;
	config.type = ActorType::HERO;
	config.health = 100;
	config.speed = 210;
	config.size = 1.f;
	config.weaponType = WeaponType::RANGE;
	return config;
}

ActorConfig ActorConfig::getMonsterConfig(const MonsterType& type)
{
	ActorConfig config;
	config.type = ActorType::MONSTER;
	switch (type)
	{
	case MonsterType::SUPER_LIGHT:
		config.health = 10;
		config.speed = 220;
		config.size = 0.4f;
		break;

	case MonsterType::LIGHT:
		config.health = 50;
		config.speed = 190;
		config.size = 0.6f;
		break;

	case MonsterType::MEDIUM:
		config.health = 100;
		config.speed = 120;
		config.size = 1.0f;
		break;

	case MonsterType::HEAVY:
		config.health = 150;
		config.speed = 60;
		config.size = 2.1f;
		break;

	default:
		break;
	}
	config.weaponType = WeaponType::MELEE;

	// TODO: Implement real spawn positions
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-0.5f, 0.5f);
	float posX = dis(gen);
	float posY = dis(gen);

	posX *= 1024.f;
	if (posX > 0.f)
	{
		posX += 1024.f;
	}

	posY *= 768.f;
	if (posY > 0.f)
	{
		posY += 768.f;
	}
	config.position.x = posX;
	config.position.y = posY;

	return config;
}

const ActorType ActorConfig::getType() const
{
	return type;
}
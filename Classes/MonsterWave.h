#pragma once
#include <vector>
#include "ActorConfig.h"

class MonsterWave
{
public:
	MonsterWave();
	~MonsterWave();
	double delay;
	const vector<ActorConfig>& getConfigs() const { return configs; };
private:
	vector<ActorConfig> configs;
};

MonsterWave::MonsterWave():
	delay(10)
{
	auto config = ActorConfig(ActorType::MONSTER);
	config.health = 20;
	config.speed = 300;
	config.position.set(-1200, -100);
	configs.push_back(config);

	config.speed = 250;
	config.position.set(-900, -200);
	configs.push_back(config);

	config.speed = 250;
	config.position.set(200, -700);
	configs.push_back(config);

	config.speed = 250;
	config.position.set(1250, -400);
	configs.push_back(config);

	config.health = 100;
	config.speed = 120;
	config.position.set(1600, 200);
	configs.push_back(config);

	config.health = 160;
	config.speed = 70;
	config.position.set(1650, 220);
	configs.push_back(config);

}

MonsterWave::~MonsterWave()
{
}
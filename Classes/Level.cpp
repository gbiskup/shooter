#include <random>
#include "Level.h"

using namespace std;

Level::Level()
{
	MonsterWave wave1;
	wave1.delay = 8;
	wave1.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	wave1.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	wave1.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	wave1.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	wave1.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	wave1.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	addWave(wave1);

	MonsterWave wave2;
	wave2.delay = 4;
	wave2.addMonster(ActorConfig::getMonsterConfig(MonsterType::LIGHT));
	wave2.addMonster(ActorConfig::getMonsterConfig(MonsterType::LIGHT));
	wave2.addMonster(ActorConfig::getMonsterConfig(MonsterType::MEDIUM));
	addWave(wave2);

	MonsterWave wave3;
	wave3.delay = 10;
	wave3.addMonster(ActorConfig::getMonsterConfig(MonsterType::HEAVY));
	wave3.addMonster(ActorConfig::getMonsterConfig(MonsterType::MEDIUM));
	wave3.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	wave3.addMonster(ActorConfig::getMonsterConfig(MonsterType::SUPER_LIGHT));
	addWave(wave3);
}

const MonsterWave Level::getCurrentWave() const
{
	return waves.at(currentWave);
}

void Level::setRandomWave()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, waves.size() - 1);
	currentWave = dis(gen);
}

bool Level::isOver()
{
	return waves.size() == 0;
}

void Level::addWave(const MonsterWave wave)
{
	waves.push_back(wave);
}

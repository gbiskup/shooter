#pragma once
#include <vector>
#include "ActorConfig.h"

using namespace std;

class MonsterWave
{
public:
	double delay;
	const vector<ActorConfig>& getConfigs() const { return configs; };
	void addMonster(const ActorConfig& config);
private:
	vector<ActorConfig> configs;
};
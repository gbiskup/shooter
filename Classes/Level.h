#pragma once
#include <vector>
#include "MonsterWave.h"

using namespace std;

class Level
{
public:
	Level();
	bool isOver();
	void addWave(const MonsterWave);
	void setRandomWave();
	const MonsterWave getCurrentWave() const;
private:
	int currentWave = 0;
	vector<MonsterWave> waves;
};
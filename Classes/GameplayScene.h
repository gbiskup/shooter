#pragma once
#include <string>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class GameplayScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

private:
	CREATE_FUNC(GameplayScene);
};
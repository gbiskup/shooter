#pragma once
#include <string>
#include "cocos2d.h"
#include "GameplayScene.h"

using namespace cocos2d;
using namespace std;

class MainMenuScene : public Layer
{
public:
	~MainMenuScene();
	static Scene* createScene();
	bool init();
	CREATE_FUNC(MainMenuScene);

private:
	Menu * menu;
	void exitCallback(const Ref * sender);
	void startCallback(const Ref* sender);
	void addItem(const string&, const ccMenuCallback&);
};
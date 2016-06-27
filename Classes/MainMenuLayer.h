#pragma once
#include <string>
#include "cocos2d.h"
#include "GameplayLayer.h"

using namespace cocos2d;
using namespace std;

class MainMenuLayer : public Layer
{
public:
	~MainMenuLayer();
	static Scene* createScene();
	bool init();
	CREATE_FUNC(MainMenuLayer)

private:
	Menu * menu;
	void exitCallback(const Ref * sender);
	void startCallback(const Ref* sender);
	void addItem(const string&, const ccMenuCallback&);
};
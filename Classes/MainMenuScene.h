#pragma once
#include <string>
#include "cocos2d.h"
#include "GameplayScene.h"

using namespace cocos2d;
using namespace std;

class MainMenuScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenuScene);

private:
	Menu * menu;
	void exitCallback(Ref* sender);
	void startCallback(Ref* sender);
	void addItem(const string&, const ccMenuCallback&);


};
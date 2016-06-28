#pragma once
#include <string>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class MainMenuLayer : public Layer
{
public:
	static Scene* createScene(); // Creates empty scene and adds this layer there
	bool init();
	CREATE_FUNC(MainMenuLayer) // Macro doing Obj-C style initialization and returning autorlease pointer

private:
	void createMenu();
	void addMenuItem(const string&, const ccMenuCallback&);
	void exitCallback(const Ref * sender);
	void startCallback(const Ref* sender);
	Menu * menu;
};
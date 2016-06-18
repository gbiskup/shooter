#pragma once
#include <string>
#include "cocos2d.h"
#include "KeyboardController.h"

using namespace cocos2d;
using namespace std;

class GameplayScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void update(float) override;
	void returnToMenu();

	CREATE_FUNC(GameplayScene);

private:
	KeyboardController* keyboardController;
	void initKeyobardController();
};
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
	void returnToMenu();
	void update(float) override;

	CREATE_FUNC(GameplayScene);

private:
	void initKeyobardController();
	void initPlayer();
	KeyboardController* keyboardController;
	PhysicsWorld* world;

};
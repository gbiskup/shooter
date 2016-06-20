#pragma once
#include <string>
#include "cocos2d.h"
#include "KeyboardController.h"
#include "Hero.h"

using namespace cocos2d;
using namespace std;

class GameplayScene : public Layer
{
public:
	~GameplayScene();
	static Scene* createScene();
	virtual bool init();
	void update(float) override;

	CREATE_FUNC(GameplayScene);

private:
	void initKeyboardController();
	void initPlayer();
	void returnToMenu();
	KeyboardController* keyboardController;
	PhysicsWorld* world;
	Hero* hero;
};
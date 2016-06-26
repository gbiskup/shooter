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
	bool init();
	void update(float) override;

	CREATE_FUNC(GameplayScene)

private:
	void initKeyboardController();
	void initMouseController();
	void addCollisionListener();
	void mouseDownHandler(EventMouse*);
	void mouseUpHandler(EventMouse*);
	void mouseMoveHandler(EventMouse*);
	bool onCollisionBegin(PhysicsContact&);

	void initHero();
	void returnToMenu();

	MouseController * mouseController;
	EventListenerMouse * mouseEventListener;

	KeyboardController* keyboardController;
	PhysicsWorld* world;
	Hero* hero;
};
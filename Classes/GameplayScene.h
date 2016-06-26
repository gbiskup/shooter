#pragma once
#include <string>
#include "cocos2d.h"
#include "KeyboardController.h"
#include "CollisionController.h"
#include "ActorFactory.h"
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
	void initCollisionController();
	void mouseDownHandler(EventMouse*);
	void mouseUpHandler(EventMouse*);
	void mouseMoveHandler(EventMouse*);

	void initHero();
	void returnToMenu();
	
	ActorFactory actorFactory;

	EventListenerMouse * mouseEventListener;
	KeyboardController* keyboardController;
	CollisionController collisionController;

	PhysicsWorld* world;
	Hero* hero;
};
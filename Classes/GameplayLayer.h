#pragma once
#include "cocos2d.h"
#include "KeyboardController.h"
#include "CollisionController.h"
#include "ActorFactory.h"
#include "Hero.h"

using namespace cocos2d;
using namespace std;

class GameplayLayer : public Layer
{
public:
	~GameplayLayer();
	static Scene* createScene();
	static void initWorld( Scene* );
	bool init();
	void update(float) override;
	CREATE_FUNC(GameplayLayer)

private:
	void initKeyboardController();
	void initMouseController();
	void initCollisionController();
	void mouseDownHandler(EventMouse*);
	void mouseUpHandler(EventMouse*);
	void mouseMoveHandler(EventMouse*);

	void initHero();
	void returnToMenu();
	void showGameOver();
	
	ActorFactory actorFactory;

	EventListenerMouse * mouseEventListener;
	KeyboardController* keyboardController;
	CollisionController collisionController;

	PhysicsWorld* world;
	Hero* hero;
};
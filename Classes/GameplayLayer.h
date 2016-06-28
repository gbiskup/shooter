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
	static void initWorld(Scene*);
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
	void initHealtLabel();
	void updateHealthLabel();
	Vec2 getScreenCenter();

	ActorFactory actorFactory;
	KeyboardController keyboardController;
	CollisionController collisionController;
	EventListenerMouse * mouseEventListener;
	EventListenerKeyboard * keyboardListener;
	PhysicsWorld* world;
	Hero* hero;
	Label* healthLabel;
	int lastShownHealth = 0; // To prevent constant health label refreshing
};
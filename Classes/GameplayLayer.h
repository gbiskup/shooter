#pragma once
#include "cocos2d.h"
#include "KeyboardController.h"
#include "CollisionController.h"
#include "ActorFactory.h"
#include "Hero.h"
#include "Level.h"

using namespace cocos2d;
using namespace std;

class MonsterWave;

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
	void initLevel();
	void mouseDownHandler(EventMouse*);
	void mouseUpHandler(EventMouse*);
	void mouseMoveHandler(EventMouse*);

	void initHero();
	void spawnMonsters();
	void returnToMenu();
	void showGameOver();
	void initHealtLabel();
	void updateHealthLabel();
	void updateMonsterWave(float);
	void startNextWave();
	Vec2 getScreenCenter();

	Level currentLevel;
	ActorFactory actorFactory;
	KeyboardController keyboardController;
	CollisionController collisionController;
	EventListenerMouse * mouseEventListener;
	EventListenerKeyboard * keyboardListener;
	EventListenerPhysicsContact * contactListener;
	PhysicsWorld* world;
	Hero* hero;
	Label* healthLabel;
	float timeToSpawn = 0;
	int lastShownHealth = 0; // To prevent constant health label refreshing
	const int firstWaveDelay = 3;
};
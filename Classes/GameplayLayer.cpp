#include <string>
#include "AssetConstants.h"
#include "GameplayLayer.h"
#include "MainMenuLayer.h"
#include "GameActor.h"
#include "ActorFactory.h"
#include "CollisionBitMasks.h"
#include "ActionsController.h"
#include "ActorConfig.h"
#include "MonsterWave.h"

GameplayLayer::~GameplayLayer()
{
	getEventDispatcher()->removeEventListener(mouseEventListener);
	getEventDispatcher()->removeEventListener(keyboardListener);
	getEventDispatcher()->removeEventListener(contactListener);
}

Scene* GameplayLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	initWorld(scene);
	return scene;
}

void GameplayLayer::initWorld( Scene* scene )
{
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 30); // Bounds preventing player or bullets leaving the screen
	edgeBody->setDynamic(false);
	edgeBody->setCategoryBitmask(static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));
	edgeBody->setCollisionBitmask(static_cast<int>(CollisionBitmasks::BULLET) | static_cast<int>(CollisionBitmasks::HERO)); // Don't bother colliding with monsters
	edgeBody->setContactTestBitmask(static_cast<int>(CollisionBitmasks::BULLET)); // Trigger events only for bullets. Default collision handling for hero.

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	scene->addChild(edgeNode);

	auto layer = GameplayLayer::create();
	scene->addChild(layer);
}

bool GameplayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initHealtLabel();
	initHero();
	initKeyboardController();
	initMouseController();
	initCollisionController();
	initLevel();
	this->scheduleUpdate();
	return true;
}

void GameplayLayer::initLevel()
{
	currentLevel.setRandomWave();
	timeToSpawn = firstWaveDelay;
}

void GameplayLayer::startNextWave()
{
	timeToSpawn = currentLevel.getCurrentWave().delay;
	currentLevel.setRandomWave();
}

void GameplayLayer::update(float delta)
{
	updateMonsterWave(delta);
	if (hero->isDead())
	{
		unscheduleUpdate();
		showGameOver();
	}
	updateHealthLabel();
}

void GameplayLayer::updateMonsterWave(float delta)
{
	if (!currentLevel.isOver())
	{
		timeToSpawn -= delta;
		if (timeToSpawn <= 0)
		{
			spawnMonsters();
			startNextWave();
		}
	}
}

void GameplayLayer::initHero()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto config = ActorConfig::getHeroConfig();
	config.position.x = visibleSize.width / 2;
	config.position.y = visibleSize.height / 2;
	hero = dynamic_cast<Hero*>(actorFactory.createActorNode(config));
	addChild(hero);
}

void GameplayLayer::spawnMonsters()
{
	auto wave = currentLevel.getCurrentWave();
	for (auto& config : wave.getConfigs())
	{
		auto monster = dynamic_cast<Monster*>(actorFactory.createActorNode(config));
		addChild(monster, 0);
		monster->followTarget(hero);
	}

}

void GameplayLayer::initMouseController()
{
	mouseEventListener = EventListenerMouse::create();

	//Simplify std::binds with cocos macro
	mouseEventListener->onMouseDown = CC_CALLBACK_1(GameplayLayer::mouseDownHandler, this);
	mouseEventListener->onMouseUp = CC_CALLBACK_1(GameplayLayer::mouseUpHandler, this);
	mouseEventListener->onMouseMove = CC_CALLBACK_1(GameplayLayer::mouseMoveHandler, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseEventListener, this);
}

void GameplayLayer::initCollisionController()
{
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CollisionController::onCollisionBegin, &collisionController);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionController::onCollisionEnded, &collisionController);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameplayLayer::mouseDownHandler(EventMouse * eventMouse)
{
	hero->actionsController.startAction(ActorActionType::ATTACK);
}

void GameplayLayer::mouseUpHandler(EventMouse * eventMouse)
{
	hero->actionsController.stopAction(ActorActionType::ATTACK);
}

void GameplayLayer::mouseMoveHandler(EventMouse * eventMouse)
{
	auto mouseVector = eventMouse->getLocationInView();
	hero->lookAt(mouseVector);
}

void GameplayLayer::initKeyboardController()
{
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardController::handleKeyPressed, &keyboardController);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(KeyboardController::handleKeyReleased, &keyboardController);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Hero controls
	auto actionController = &hero->actionsController;
	keyboardController.registerKeyDownCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_UP));
	keyboardController.registerKeyDownCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_DOWN));
	keyboardController.registerKeyDownCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_LEFT));
	keyboardController.registerKeyDownCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_RIGHT));

	keyboardController.registerKeyUpCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_UP));
	keyboardController.registerKeyUpCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_DOWN));
	keyboardController.registerKeyUpCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_LEFT));
	keyboardController.registerKeyUpCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_RIGHT));

	// Layer controls
	keyboardController.registerKeyDownCallback(EventKeyboard::KeyCode::KEY_ESCAPE, CC_CALLBACK_0(GameplayLayer::returnToMenu, this));
}

void GameplayLayer::initHealtLabel()
{
	healthLabel = Label::createWithTTF("", FontPaths::MAIN_FONT, 24);
	healthLabel->setAnchorPoint(Vec2(1.0, 1.0));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	healthLabel->setPosition(Vec2(visibleSize.width, visibleSize.height));
	addChild(healthLabel);
}

void GameplayLayer::updateHealthLabel()
{
	if (lastShownHealth != hero->getHealth())
	{
		lastShownHealth = hero->getHealth();
		string labelText = "Health: " + std::to_string(lastShownHealth);
		healthLabel->setString(labelText);
	}
}

Vec2 GameplayLayer::getScreenCenter()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return Vec2(visibleSize.width / 2, visibleSize.height / 2);
}

void GameplayLayer::showGameOver()
{
	auto gameOverLabel = Label::createWithTTF("The hero is dead. Esc - get back to menu.", FontPaths::MAIN_FONT, 24);
	gameOverLabel->setPosition(getScreenCenter());
	addChild(gameOverLabel);
}

void GameplayLayer::returnToMenu()
{
	Director::getInstance()->replaceScene(MainMenuLayer::createScene());
}

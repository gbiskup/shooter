#include <string>
#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "GameActor.h"
#include "ActorFactory.h"

GameplayScene::~GameplayScene()
{
	log("Destroy gameplay");
	keyboardController->disable();
}

Scene* GameplayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	auto layer = GameplayScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameplayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initKeyboardController();
	initPlayer();
	this->scheduleUpdate();
	return true;
}

void GameplayScene::update(float delta)
{
	
}

void GameplayScene::initPlayer()
{
	ActorFactory factory;
	hero = dynamic_cast<Hero*>(factory.createActorOfType(ActorType::HERO));
	addChild(hero);
}

void GameplayScene::initKeyboardController()
{
	keyboardController = KeyboardController::create();
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_ESCAPE, CC_CALLBACK_0(GameplayScene::returnToMenu, this));
	keyboardController->enable(this);
}

void GameplayScene::returnToMenu()
{
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

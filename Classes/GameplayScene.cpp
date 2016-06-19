#include <string>
#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "GameActor.h"

Scene* GameplayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameplayScene::create();
	layer->setPhysicsWorld( scene->getPhysicsWorld() );
	scene->addChild(layer);
	return scene;
}

bool GameplayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initKeyobardController();
	initPlayer();
	this->scheduleUpdate();
	return true;
}

void GameplayScene::update(float delta)
{
	
}

void GameplayScene::initPlayer()
{
	auto player = GameActor::create();
	addChild(player);
}

void GameplayScene::initKeyobardController()
{
	keyboardController = KeyboardController::create();
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_ESCAPE, CC_CALLBACK_0(GameplayScene::returnToMenu, this));
	keyboardController->enable(this);
}

void GameplayScene::returnToMenu()
{
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

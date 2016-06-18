#include <string>
#include "GameplayScene.h"
#include "MainMenuScene.h"

Scene* GameplayScene::createScene()
{
	auto scene = Scene::create();
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
	initKeyobardController();
	this->scheduleUpdate();
	return true;
}

void GameplayScene::update(float delta)
{
	
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

#include "GameplayScene.h"
#include <string>

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
	return true;
}

void GameplayScene::initKeyobardController()
{
	auto keyboardController = KeyboardController::create();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(static_cast<EventListenerKeyboard*>(keyboardController), this);
}
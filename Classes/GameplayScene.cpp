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
	return true;
}
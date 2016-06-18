#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include <string>

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	menu = Menu::create();

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	addItem("Start game", CC_CALLBACK_1(MainMenuScene::startCallback, this));
	addItem("Exit", CC_CALLBACK_1(MainMenuScene::exitCallback, this));
	menu->alignItemsVerticallyWithPadding(20.f);

	menu->setPosition(Vec2 (visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(menu);

	return true;
}

void MainMenuScene::startCallback(Ref* sender)
{
	Director::getInstance()->replaceScene(GameplayScene::createScene());
}

void MainMenuScene::exitCallback(Ref* sender)
{
	Director::getInstance()->end();
}

void MainMenuScene::addItem(const string & text, const ccMenuCallback& callback)
{
	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
	auto menuItem = MenuItemLabel::create(label, callback);
	menu->addChild(menuItem);
}
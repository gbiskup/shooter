#include <string>
#include "MainMenuLayer.h"
#include "GameplayLayer.h"
#include "AssetConstants.h"

Scene* MainMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuLayer::create();
	scene->addChild(layer);
	return scene;
}

// Objective-C style intialization.. 
bool MainMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	createMenu();
	return true;
}

void MainMenuLayer::createMenu()
{
	menu = Menu::create();
	this->addChild(menu);

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	addMenuItem("Start game", CC_CALLBACK_1(MainMenuLayer::startCallback, this));
	addMenuItem("Exit", CC_CALLBACK_1(MainMenuLayer::exitCallback, this));

	menu->alignItemsVerticallyWithPadding(20.f);
}

void MainMenuLayer::startCallback(const Ref* sender)
{
	Director::getInstance()->replaceScene(GameplayLayer::createScene());
}

void MainMenuLayer::exitCallback(const Ref* sender)
{
	Director::getInstance()->end();
}

void MainMenuLayer::addMenuItem(const string & text, const ccMenuCallback& callback)
{
	auto label = Label::createWithTTF(text, FontPaths::MAIN_FONT, 24);
	auto menuItem = MenuItemLabel::create(label, callback);
	menu->addChild(menuItem);
}
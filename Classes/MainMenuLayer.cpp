#include <string>
#include "MainMenuLayer.h"
#include "AssetConstants.h"

MainMenuLayer::~MainMenuLayer()
{
	log("Menu is destroyed");
}

Scene* MainMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	menu = Menu::create();

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	addItem("Start game", CC_CALLBACK_1(MainMenuLayer::startCallback, this));
	addItem("Exit", CC_CALLBACK_1(MainMenuLayer::exitCallback, this));
	menu->alignItemsVerticallyWithPadding(20.f);

	menu->setPosition(Vec2 (visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(menu);

	return true;
}

void MainMenuLayer::startCallback(const Ref* sender)
{
	Director::getInstance()->replaceScene(GameplayLayer::createScene());
}

void MainMenuLayer::exitCallback(const Ref* sender)
{
	Director::getInstance()->end();
}

void MainMenuLayer::addItem(const string & text, const ccMenuCallback& callback)
{
	auto label = Label::createWithTTF(text, FontPaths::MAIN_FONT, 24);
	auto menuItem = MenuItemLabel::create(label, callback);
	menu->addChild(menuItem);
}
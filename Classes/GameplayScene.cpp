#include <string>
#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "GameActor.h"
#include "ActorFactory.h"
#include "ActionState.h"
#include "CollisionBitMasks.h"

GameplayScene::~GameplayScene()
{
	log("Destroy gameplay");
	getEventDispatcher()->removeEventListener(mouseEventListener);
	keyboardController->disable();
}

Scene* GameplayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 30);
	edgeBody->setDynamic(false);
	edgeBody->setCategoryBitmask(static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));
	edgeBody->setCollisionBitmask(static_cast<int>(CollisionBitmasks::BULLET) | static_cast<int>(CollisionBitmasks::HERO));
	edgeBody->setContactTestBitmask(static_cast<int>( CollisionBitmasks::BULLET ));
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	scene->addChild(edgeNode);

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
	initHero();
	initKeyboardController();
	initMouseController();
	addCollisionListener();
	this->scheduleUpdate();
	return true;
}

void GameplayScene::update(float delta)
{
	
}

void GameplayScene::initHero()
{
	ActorFactory factory;
	hero = dynamic_cast<Hero*>(factory.createActorOfType(ActorType::HERO));
	addChild(hero);

	auto monster = factory.createActorOfType(ActorType::MONSTER);
	addChild(monster);
}

void GameplayScene::initMouseController()
{
	mouseEventListener = EventListenerMouse::create();
	mouseEventListener->onMouseDown = CC_CALLBACK_1(GameplayScene::mouseDownHandler, this);
	mouseEventListener->onMouseUp = CC_CALLBACK_1(GameplayScene::mouseUpHandler, this);
	mouseEventListener->onMouseMove = CC_CALLBACK_1(GameplayScene::mouseMoveHandler, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseEventListener, this);
}

void GameplayScene::addCollisionListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CollisionController::onCollisionBegin, &collisionController);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameplayScene::mouseDownHandler(EventMouse * eventMouse)
{
	hero->actionsController.startAction(ActionType::ATTACK);
}

void GameplayScene::mouseUpHandler(EventMouse * eventMouse)
{
	hero->actionsController.stopAction(ActionType::ATTACK);
}

void GameplayScene::mouseMoveHandler(EventMouse * eventMouse)
{
	auto mouseVector = eventMouse->getLocationInView();
	hero->lookAt(mouseVector);
}

void GameplayScene::initKeyboardController()
{
	keyboardController = KeyboardController::create();
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_ESCAPE, CC_CALLBACK_0(GameplayScene::returnToMenu, this));

	auto actionController = &hero->actionsController;
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::startAction, actionController, ActionType::MOVE_UP));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::startAction, actionController, ActionType::MOVE_DOWN));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::startAction, actionController, ActionType::MOVE_LEFT));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::startAction, actionController, ActionType::MOVE_RIGHT));

	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActionType::MOVE_UP));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActionType::MOVE_DOWN));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActionType::MOVE_LEFT));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActionType::MOVE_RIGHT));

	keyboardController->enable(this);
}

void GameplayScene::returnToMenu()
{
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

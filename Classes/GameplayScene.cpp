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
	initCollisionController();
	this->scheduleUpdate();
	return true;
}

void GameplayScene::update(float delta)
{
	
}

void GameplayScene::initHero()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	hero = dynamic_cast<Hero*>(actorFactory.createActorOfType( ActorType::HERO, Point( visibleSize.width/2, visibleSize.height/2 )));
	addChild(hero);

	auto monster = actorFactory.createMonster( Point( -visibleSize.width/4, visibleSize.height/3 ));
	addChild(monster);
	monster->followTarget( hero );
}

void GameplayScene::initMouseController()
{
	mouseEventListener = EventListenerMouse::create();
	mouseEventListener->onMouseDown = CC_CALLBACK_1(GameplayScene::mouseDownHandler, this);
	mouseEventListener->onMouseUp = CC_CALLBACK_1(GameplayScene::mouseUpHandler, this);
	mouseEventListener->onMouseMove = CC_CALLBACK_1(GameplayScene::mouseMoveHandler, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseEventListener, this);
}

void GameplayScene::initCollisionController()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CollisionController::onCollisionBegin, &collisionController);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionController::onCollisionEnded, &collisionController);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameplayScene::mouseDownHandler(EventMouse * eventMouse)
{
	hero->actionsController.startAction(ActorActionType::ATTACK);
}

void GameplayScene::mouseUpHandler(EventMouse * eventMouse)
{
	hero->actionsController.stopAction(ActorActionType::ATTACK);
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
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_UP));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_DOWN));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_LEFT));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::startAction, actionController, ActorActionType::MOVE_RIGHT));

	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_UP));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_DOWN));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_LEFT));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::stopAction, actionController, ActorActionType::MOVE_RIGHT));

	keyboardController->enable(this);
}

void GameplayScene::returnToMenu()
{
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

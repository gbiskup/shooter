#include "GameplayLayer.h"
#include "MainMenuLayer.h"
#include "GameActor.h"
#include "ActorFactory.h"
#include "CollisionBitMasks.h"
#include "ActionsController.h"

GameplayLayer::~GameplayLayer()
{
	log("Destroy gameplay");
	getEventDispatcher()->removeEventListener(mouseEventListener);
	keyboardController->disable();
}

Scene* GameplayLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	initWorld(scene);
	return scene;
}

void GameplayLayer::initWorld( Scene* scene )
{
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 30);
	edgeBody->setDynamic(false);
	edgeBody->setCategoryBitmask(static_cast<int>(CollisionBitmasks::WORLD_BOUNDS));
	edgeBody->setCollisionBitmask(static_cast<int>(CollisionBitmasks::BULLET) | static_cast<int>(CollisionBitmasks::HERO));
	edgeBody->setContactTestBitmask(static_cast<int>(CollisionBitmasks::BULLET));
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	scene->addChild(edgeNode);

	auto layer = GameplayLayer::create();
	scene->addChild(layer);
}

bool GameplayLayer::init()
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

void GameplayLayer::update(float delta)
{
	if (hero->isDead())
	{
		unscheduleUpdate();
		showGameOver();
	}
}

void GameplayLayer::showGameOver()
{

}

void GameplayLayer::initHero()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	hero = dynamic_cast<Hero*>(actorFactory.createActorOfType( ActorType::HERO, Point( visibleSize.width/2, visibleSize.height/2 )));
	addChild(hero);

	auto monster = actorFactory.createMonster( Point( -visibleSize.width/4, visibleSize.height/3 ));
	addChild(monster);
	monster->followTarget( hero );
}

void GameplayLayer::initMouseController()
{
	mouseEventListener = EventListenerMouse::create();
	mouseEventListener->onMouseDown = CC_CALLBACK_1(GameplayLayer::mouseDownHandler, this);
	mouseEventListener->onMouseUp = CC_CALLBACK_1(GameplayLayer::mouseUpHandler, this);
	mouseEventListener->onMouseMove = CC_CALLBACK_1(GameplayLayer::mouseMoveHandler, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseEventListener, this);
}

void GameplayLayer::initCollisionController()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CollisionController::onCollisionBegin, &collisionController);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionController::onCollisionEnded, &collisionController);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameplayLayer::mouseDownHandler(EventMouse * eventMouse)
{
	hero->actionsController.startAction(ActorActionType::ATTACK);
}

void GameplayLayer::mouseUpHandler(EventMouse * eventMouse)
{
	hero->actionsController.stopAction(ActorActionType::ATTACK);
}

void GameplayLayer::mouseMoveHandler(EventMouse * eventMouse)
{
	auto mouseVector = eventMouse->getLocationInView();
	hero->lookAt(mouseVector);
}

void GameplayLayer::initKeyboardController()
{
	keyboardController = KeyboardController::create();
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_ESCAPE, CC_CALLBACK_0(GameplayLayer::returnToMenu, this));

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

void GameplayLayer::returnToMenu()
{
	Director::getInstance()->replaceScene(MainMenuLayer::createScene());
}

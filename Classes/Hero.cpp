#include "Hero.h"
#include "KeyboardController.h"

Hero::~Hero()
{
	log("Hero destroyed");
	keyboardController->disable();
	getEventDispatcher()->removeEventListener(mouseEventListener);
	//getEven
}

bool Hero::init()
{
	if (!GameActor::init())
	{
		return false;
	}
	initMouseController();
	initKeyboardController();
	return true;
}

void Hero::initMouseController()
{
	//auto mouseEventListener = EventListenerMouse::create();
	mouseEventListener = EventListenerMouse::create();
	mouseEventListener->onMouseDown = CC_CALLBACK_1(Hero::mouseDownHandler, this);
	mouseEventListener->onMouseUp = CC_CALLBACK_1(Hero::mouseUpHandler, this);
	mouseEventListener->onMouseMove = CC_CALLBACK_1(Hero::mouseMoveHandler, this);
	
	getEventDispatcher()->addEventListenerWithFixedPriority(mouseEventListener, 1);
}

void Hero::initKeyboardController()
{
	keyboardController = KeyboardController::create();
	keyboardController->enable(this);

	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_UP));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_DOWN));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_LEFT));
	keyboardController->registerKeyDownCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::startAction, &actionsController, ActionsController::ActionType::MOVE_RIGHT));

	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_W, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_UP));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_S, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_DOWN));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_A, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_LEFT));
	keyboardController->registerKeyUpCallback(EventKeyboard::KeyCode::KEY_D, CC_CALLBACK_0(ActionsController::stopAction, &actionsController, ActionsController::ActionType::MOVE_RIGHT));
}

void Hero::mouseDownHandler(EventMouse * eventMouse)
{
	log("Mouse down");
}

void Hero::mouseUpHandler(EventMouse * eventMouse)
{
	log("Mouse up");
}

void Hero::mouseMoveHandler(EventMouse * eventMouse)
{
	auto mouseVector = eventMouse->getLocationInView();

	auto position = getPosition();
	position.subtract(mouseVector);
	//CC_RADIANS_TO_DEGREES(mousePosition.getAngle(getPosition())
	setRotation(-CC_RADIANS_TO_DEGREES(position.getAngle()));
	//angle = atan2(deltay, deltax) * (180 / PI);
}

#include "Hero.h"
#include "KeyboardController.h"

Hero::~Hero()
{
	log("Hero destroyed");
	getEventDispatcher()->removeEventListener(mouseEventListener);
}

bool Hero::init()
{
	if (!GameActor::init())
	{
		return false;
	}
	initMouseController();
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

void Hero::mouseDownHandler(EventMouse * eventMouse)
{
	actionsController.startAction( ActionType::ATTACK );
}

void Hero::mouseUpHandler(EventMouse * eventMouse)
{
	actionsController.stopAction( ActionType::ATTACK );
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

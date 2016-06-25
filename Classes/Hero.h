#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "KeyboardController.h"
#include "MouseController.h"

using namespace cocos2d;

class Hero : public GameActor
{
public:
	~Hero();
	bool init();
	CREATE_FUNC(Hero)

private:
	void initMouseController();
	void mouseDownHandler(EventMouse*);
	void mouseUpHandler(EventMouse*);
	void mouseMoveHandler(EventMouse*);
	MouseController * mouseController;
	EventListenerMouse * mouseEventListener;
};
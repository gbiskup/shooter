#pragma once
#include "cocos2d.h"
#include "GameActor.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "Weapon.h"

using namespace cocos2d;

class Hero : public GameActor
{
public:
	~Hero();
	bool init();
	void pickUpWeapon(Weapon*);
	CREATE_FUNC(Hero)

private:
	void initMouseController();
	void initKeyboardController();
	void mouseDownHandler(EventMouse*);
	void mouseUpHandler(EventMouse*);
	void mouseMoveHandler(EventMouse*);
	KeyboardController * keyboardController;
	MouseController * mouseController;
	EventListenerMouse * mouseEventListener;
	Weapon* weapon;
};
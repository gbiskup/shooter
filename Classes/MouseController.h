#pragma once
#include <map>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class MouseController : private EventListenerMouse
{
public:
	bool init();
	void enable(Node * target);
	CREATE_FUNC(MouseController);
};
#include "GameActor.h"

bool GameActor::init()
{
	if (!Node::init())
	{
		return false;
	}
	/*auto rectNode = DrawNode::create();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(-50, -50);
	rectangle[1] = Vec2(50, -50);
	rectangle[2] = Vec2(50, 50);
	rectangle[3] = Vec2(-50, 50);

	Color4F white(1, 1, 1, 1);
	rectNode->drawPolygon(rectangle, 4, white, 1, white);
	this->addChild(rectNode);*/

	return true;
}

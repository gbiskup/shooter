#pragma once

enum class CollisionBitmasks
{
	HERO = 1,
	MONSTER = 1 << 1,
	BULLET = 1 << 2,
	WORLD_BOUNDS = 1 << 3,
	DEAD_BODY = 1 << 4,
	ALL = 0xffffff
};
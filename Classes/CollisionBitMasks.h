#pragma once

// Physics categories definition. Used for handling non standard collisions
enum class CollisionBitmasks
{
	NONE = 0,
	HERO = 1,
	MONSTER = 1 << 1,
	BULLET = 1 << 2,
	WORLD_BOUNDS = 1 << 3,
	DEAD_BODY = 1 << 4,
	ALL = 0xffffff
};
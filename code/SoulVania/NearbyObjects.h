#pragma once

#include "Door.h"
#include "Trigger.h"

// Some collision result with important objects will be saved
	// for future references
struct NearbyObjects
{
	Trigger* nextMap = nullptr;

	Trigger* stair = nullptr;
	Direction stairHitDirection = Direction::None;

	Door* door = nullptr;
	Direction doorHitDirection = Direction::None;
};
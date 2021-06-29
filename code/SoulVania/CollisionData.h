#pragma once

#include "CollisionResult.h"

struct CollisionData
{
	CollisionResults collisionResults;
	base::Vector2 minTime = base::Vector2{ -1, -1 };
	base::Vector2 minNormal = base::Vector2::Zero();
};
#pragma once

#include "Player.h"
#include "ObjectCollection.h"

struct UpdateData
{
	GameTime gameTime;
	RectF viewport;
	Player* player;
	bool isStopwatchActive;
	ObjectCollection* objects;
	std::vector<GameObject*>* collisionObjects;
};
#pragma once

#include "IReceiver.h"
#include "GameTime.h"
#include "Vector2.h"

class IMovementSystem : public IReceiver
{
public:
	virtual void Enabled(bool value) = 0;
	virtual bool Enabled() = 0;

	virtual base::Vector2 GetDistance() = 0;
	virtual void SetDistance(base::Vector2 distance) = 0;

	virtual void Update(GameTime gameTime) = 0;
	virtual ~IMovementSystem() {}
};
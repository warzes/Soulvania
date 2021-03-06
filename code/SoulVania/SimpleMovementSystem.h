#pragma once

#include "MovementSystem.h"

// Basic movement system: distance = velocity * deltaTime
class SimpleMovementSystem : public MovementSystem
{
public:
	SimpleMovementSystem(GameObject& parent);

private:
	GameObject& parent;

	void UpdateMovement(GameTime gameTime) override;
};
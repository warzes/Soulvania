#pragma once

#include "MovementSystem.h"
#include "Player.h"

class PlayerMovementSystem : public MovementSystem
{
public:
	PlayerMovementSystem(Player& parent);

private:
	Player& parent;

	void UpdateMovement(GameTime gameTime) override;
};
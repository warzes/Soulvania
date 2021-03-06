#pragma once

#include "MovementSystem.h"
#include "GiantBat.h"

// For objects in game that have weight (player, enemy)
class GiantBatMovementSystem : public MovementSystem
{
public:
	GiantBatMovementSystem(GiantBat& parent);

	void Receive(int message) override;

private:
	GiantBat& parent;
	base::Vector2 vertex;
	float a; // coefficient in parabola's equation
	float direction;
	float speed_x;

	void OnMoveStateChanged();

	void UpdateMovement(GameTime gameTime) override;
	void UpdateLinearMovement(float deltaTime);
	void UpdateParabolicMovement(float deltaTime);
};
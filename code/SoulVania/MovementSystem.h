#pragma once

#include "IMovementSystem.h"

class GameObject;

// Basic movement system: distance = velocity * deltaTime
class MovementSystem : public IMovementSystem
{
public:
	MovementSystem();

	void Enabled(bool value) override;
	bool Enabled() override;

	base::Vector2 GetDistance() override;
	void SetDistance(base::Vector2 distance) override;

	virtual void Receive(int message) override {};
	void Update(GameTime gameTime) override;

protected:
	bool enabled;
	base::Vector2 distance; // estimated distance to move

	virtual void UpdateMovement(GameTime gameTime) = 0;
};
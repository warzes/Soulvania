#include "stdafx.h"
#include "MovementSystem.h"
#include "GameObject.h"

MovementSystem::MovementSystem()
{
	enabled = true;
}

void MovementSystem::Enabled(bool value)
{
	enabled = value;
}

bool MovementSystem::Enabled()
{
	return enabled;
}

base::Vector2 MovementSystem::GetDistance()
{
	return distance;
}

void MovementSystem::SetDistance(base::Vector2 distance)
{
	this->distance = distance;
}

void MovementSystem::Update(GameTime gameTime)
{
	if (enabled)
		UpdateMovement(gameTime);
}
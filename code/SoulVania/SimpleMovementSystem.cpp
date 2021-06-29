#include "stdafx.h"
#include "SimpleMovementSystem.h"
#include "GameObject.h"

SimpleMovementSystem::SimpleMovementSystem(GameObject& parent) : parent{ parent }
{
}

void SimpleMovementSystem::UpdateMovement(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	distance = velocity * deltaTime;
}
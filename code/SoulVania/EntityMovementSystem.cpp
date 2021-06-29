#include "stdafx.h"
#include "EntityMovementSystem.h"
#include "MathHelper.h"
#include "GameObject.h"
#include "Settings.h"

EntityMovementSystem::EntityMovementSystem(GameObject& parent, float weight) : parent{ parent }
{
	this->weight = weight;
}

void EntityMovementSystem::UpdateMovement(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	velocity.y = MathHelper::Min(velocity.y + GRAVITY, weight);
	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
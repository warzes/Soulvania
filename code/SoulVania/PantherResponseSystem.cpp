#include "stdafx.h"
#include "PantherResponseSystem.h"

PantherResponseSystem::PantherResponseSystem(Panther &parent) : parent{ parent }
{
}

GameObject &PantherResponseSystem::GetParent()
{
	return parent;
}

void PantherResponseSystem::OnTouchingGround(CollisionData collisionData)
{
	ClampDistance_Y(collisionData);
}

void PantherResponseSystem::OnFalling()
{
	parent.Jump();
}

void PantherResponseSystem::OnLanding()
{
	parent.Land();
}

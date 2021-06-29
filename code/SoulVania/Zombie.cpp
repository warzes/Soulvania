#include "stdafx.h"
#include "Zombie.h"
#include "Settings.h"

Zombie::Zombie() : Enemy{ ObjectId::Zombie }
{
}

void Zombie::WalkRight()
{
	SetFacing(Facing::Right);
	velocity.x = speed;
}

void Zombie::WalkLeft()
{
	SetFacing(Facing::Left);
	velocity.x = -speed;
}

void Zombie::StopWalking()
{
	velocity = base::Vector2::Zero();
	SetDistance(base::Vector2::Zero());
}

void Zombie::Land()
{
	if (facing == Facing::Left)
		WalkLeft();
	else
		WalkRight();
}
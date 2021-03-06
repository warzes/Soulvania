#include "stdafx.h"
#include "VampireBat.h"
#include "Settings.h"

VampireBat::VampireBat() : Enemy{ ObjectId::VampireBat }
{
	isActive = false;
}

bool VampireBat::IsActive()
{
	return isActive;
}

void VampireBat::SetActive(bool value)
{
	isActive = value;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void VampireBat::FlyRight()
{
	SetFacing(Facing::Right);
	velocity.x = speed;
}

void VampireBat::FlyLeft()
{
	SetFacing(Facing::Left);
	velocity.x = -speed;
}
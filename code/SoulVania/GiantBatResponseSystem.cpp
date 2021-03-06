#include "stdafx.h"
#include "GiantBatResponseSystem.h"
#include "Settings.h"

GiantBatResponseSystem::GiantBatResponseSystem(GiantBat& parent) : parent{ parent }
{
}

void GiantBatResponseSystem::Receive(int message)
{
	switch (message)
	{
	case PLAYER_IN_RANGE:
		parent.IsInRange(true);
		break;

	case PLAYER_OUT_OF_RANGE:
		parent.IsInRange(false);
		break;
	}
}

void GiantBatResponseSystem::Update(UpdateData& updateData)
{
}
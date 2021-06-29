#include "stdafx.h"
#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
	enabled = true;
}

void ControlSystem::Enabled(bool value)
{
	enabled = value;
}

bool ControlSystem::Enabled()
{
	return enabled;
}
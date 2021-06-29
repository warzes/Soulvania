#pragma once

#include "ControlSystem.h"
#include "Panther.h"

class PantherControlSystem : public ControlSystem
{
public:
	PantherControlSystem(Panther& parent);
	void Receive(int message) override;

private:
	Panther& parent;
};
#pragma once

#include "PoisonResponseSystem.h"
#include "HolyWater.h"

class Player;

class HolyWaterResponseSystem : public PoisonResponseSystem
{
public:
	HolyWaterResponseSystem(HolyWater& parent);

	void Receive(int message) override {};
	void Update(UpdateData& updateData) override;

private:
	HolyWater& parent;
};
#pragma once

#include "Stopwatch.h"
#include "RangedWeapon.h"

class HolyWater : public RangedWeapon
{
public:
	HolyWater();

	void StartFlaming();
	bool IsFlaming();

	void Update(UpdateData& updateData) override;

private:
	bool isFlaming;
	Stopwatch flamingTimer;
};
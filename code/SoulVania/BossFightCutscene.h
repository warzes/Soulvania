#pragma once

#include "Stopwatch.h"
#include "Cutscene.h"
#include "IBoss.h"

class BossFightCutscene : public Cutscene
{
public:
	BossFightCutscene(Stage& stage, CollisionGrid& grid, ObjectFactory& objectFactory);

	void Update(UpdateData& updateData) override;

private:
	IBoss* boss;
	Stopwatch bossWakeupTimer;
};
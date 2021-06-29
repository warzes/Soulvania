#pragma once

#include "Stopwatch.h"
#include "Cutscene.h"

class StopwatchCutscene : public Cutscene
{
public:
	StopwatchCutscene(Stage& stage);
	void Update(UpdateData& updateData) override;

private:
	Stopwatch stopwatchTimer; // A stopwatch of another stopwatch >.>
};
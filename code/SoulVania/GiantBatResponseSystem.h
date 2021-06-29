#pragma once

#include "ResponseSystem.h"
#include "GiantBat.h"

class GiantBatResponseSystem : public ResponseSystem
{
public:
	GiantBatResponseSystem(GiantBat& parent);

	void Receive(int message) override;
	void Update(UpdateData& updateData);

private:
	GiantBat& parent;
};
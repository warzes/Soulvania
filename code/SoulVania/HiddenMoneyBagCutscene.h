#pragma once

#include "Cutscene.h"
#include "Powerup.h"

class HiddenMoneyBagCutscene : public Cutscene
{
public:
	HiddenMoneyBagCutscene(
		Stage& stage,
		StageObject& stageObject,
		CollisionGrid& grid,
		ObjectFactory& objectFactory);

	void Update(UpdateData& updateData) override;

private:
	base::Vector2 moneyBagPosition;
	base::Vector2 emergeEndPoint;
	Powerup* hiddenMoneyBag;
};
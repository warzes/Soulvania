#pragma once

#include "HolyWater.h"
#include "AnimationRenderingSystem.h"

class HolyWaterRenderingSystem : public AnimationRenderingSystem
{
public:
	HolyWaterRenderingSystem(HolyWater& parent, std::string animationPath);

private:
	HolyWater& parent;
	void OnMoveStateChanged() override;
};
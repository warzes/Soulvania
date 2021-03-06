#include "stdafx.h"
#include "HolyWaterRenderingSystem.h"
#include "Animations.h"

HolyWaterRenderingSystem::HolyWaterRenderingSystem(HolyWater& parent, std::string animationPath) :
	AnimationRenderingSystem{ parent, animationPath },
	parent{ parent }
{
}

void HolyWaterRenderingSystem::OnMoveStateChanged()
{
	if (parent.IsFlaming())
		sprite->Play("holy_water_flame");
	else
		sprite->Play("holy_water");
}
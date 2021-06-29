#include "stdafx.h"
#include "VampireBatRenderingSystem.h"
#include "Settings.h"
#include "Animations.h"

VampireBatRenderingSystem::VampireBatRenderingSystem(
	VampireBat& parent,
	std::string animationPath,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	EntityRenderingSystem{ parent, animationPath, std::move(deadEffect), std::move(hitEffect) },
	parent{ parent }
{
}

void VampireBatRenderingSystem::OnMoveStateChanged()
{
	if (parent.IsActive())
		sprite->Play(FLY_ANIMATION);
	else
		sprite->Play(IDLE_ANIMATION);
}

#pragma once

#include "VampireBat.h"
#include "EntityRenderingSystem.h"

class VampireBatRenderingSystem : public EntityRenderingSystem
{
public:
	VampireBatRenderingSystem(
		VampireBat& parent,
		std::string animationPath,
		std::unique_ptr<IEffect> deadEffect,
		std::unique_ptr<IEffect> hitEffect);

private:
	VampireBat& parent;
	void OnMoveStateChanged() override;
};
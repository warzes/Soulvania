#pragma once

#include "GiantBat.h"
#include "EntityRenderingSystem.h"

class GiantBatRenderingSystem : public EntityRenderingSystem
{
public:
	GiantBatRenderingSystem(
		GiantBat& parent,
		std::string animationPath,
		std::unique_ptr<IEffect> deadEffect,
		std::unique_ptr<IEffect> hitEffect);

	void Draw(SpriteExtensions& spriteBatch) override;

private:
	GiantBat& parent;
	void OnMoveStateChanged() override;
};
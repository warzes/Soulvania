#pragma once

#include "Panther.h"
#include "EntityRenderingSystem.h"


class PantherRenderingSystem : public EntityRenderingSystem
{
public:
	PantherRenderingSystem(
		Panther& parent,
		std::string animationPath,
		std::unique_ptr<IEffect> deadEffect,
		std::unique_ptr<IEffect> hitEffect);

	void Draw(SpriteExtensions& spriteBatch) override;

private:
	Panther& parent;
	void OnMoveStateChanged() override;
};
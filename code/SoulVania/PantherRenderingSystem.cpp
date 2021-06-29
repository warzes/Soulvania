#include "stdafx.h"
#include "PantherRenderingSystem.h"
#include "Animations.h"
#include "DevTool.h"

PantherRenderingSystem::PantherRenderingSystem(
	Panther &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	EntityRenderingSystem{ parent, animationPath, std::move(deadEffect), std::move(hitEffect) },
	parent{ parent }
{
}

void PantherRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (DevTool::IsDebugging)
		DrawBoundingBox(spriteBatch, parent.GetActiveZone(), base::Color::LavenderBlue() * 0.4f);

	EntityRenderingSystem::Draw(spriteBatch);
}

void PantherRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetPantherState())
	{
		case PantherState::IDLE:
			sprite->Play(IDLE_ANIMATION);
			break;

		case PantherState::RUNNING:
			sprite->Play(RUN_ANIMATION);
			break;

		case PantherState::JUMPING:
			sprite->Play(JUMP_ANIMATION);
			break;
	}
}

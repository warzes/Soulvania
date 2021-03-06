#include "stdafx.h"
#include "WhipRenderingSystem.h"
#include "MathHelper.h"
#include "Whip.h"
#include "Settings.h"

WhipRenderingSystem::WhipRenderingSystem(Whip& parent, std::string spriteConfigPath) :
	parent{ parent }
{
	this->spriteConfigPath = spriteConfigPath;
}

AnimatedSprite& WhipRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject& WhipRenderingSystem::GetParent()
{
	return parent;
}

void WhipRenderingSystem::Receive(int message)
{
	switch (message)
	{
	case WHIP_UNLEASHED:
		OnWhipUnleashed();
		break;

	case WEAPON_WITHDRAWN:
		OnWhipWithdrawn();
		break;
	}
}

void WhipRenderingSystem::LoadContent(ContentManager& content)
{
	RenderingSystem::LoadContent(content);

	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	auto animations_12 = std::vector<std::string>{ "Whip_level_01", "Whip_level_02" }; // animation for level 1 and 2 whip
	sprite = std::make_unique<AnimatedSprite>(animationFactory, animations_12);
}

void WhipRenderingSystem::Update(GameTime gameTime)
{
	if (!sprite->IsVisible())
		return;

	// This is the attack frame, enable collision detection
	if (sprite->GetCurrentAnimation().GetCurrentFrameIndex() == 2)
		parent.GetBody().Enabled(true);

	sprite->Update();
	// Update the animation first before getting position so UpdatePositionRelativeToPlayer()
	// can access to the latest frame index
	UpdatePositionRelativeToPlayer();
}

void WhipRenderingSystem::Draw(SpriteExtensions& spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);
	spriteBatch.Draw(*sprite, parent.GetPosition());
}

void WhipRenderingSystem::OnWhipUnleashed()
{
	UpdatePositionRelativeToPlayer();

	auto level = MathHelper::Min(parent.GetLevel(), 2);

	// Play level 1 or 2 whip animation, level 3 whip is another seperate system
	sprite->Play("Whip_level_0" + std::to_string(level));
	sprite->SetVisibility(true);
}

void WhipRenderingSystem::OnWhipWithdrawn()
{
	sprite->GetCurrentAnimation().Reset();
	sprite->SetVisibility(false);
}

void WhipRenderingSystem::UpdatePositionRelativeToPlayer()
{
	auto player = parent.GetOwner();
	auto playerBbox = player->GetBoundingBox();
	auto whipBbox = parent.GetBoundingBox();
	auto currentFrameIndex = GetSprite().GetCurrentAnimation().GetCurrentFrameIndex();
	auto newPosition = base::Vector2{};

	if (parent.GetFacing() == Facing::Right)
	{
		switch (currentFrameIndex)
		{
		case 0:
			newPosition = base::Vector2{ playerBbox.left - whipBbox.Width() + 1, playerBbox.top + 14 };
			break;
		case 1:
			newPosition = base::Vector2{ playerBbox.left - whipBbox.Width(), playerBbox.top + 9 };
			break;
		case 2:
			newPosition = base::Vector2{ playerBbox.right + 8, playerBbox.top + 26 - whipBbox.Height() };
			break;
		default:
			newPosition = base::Vector2::Zero();
			break;
		}
	}
	else // Facing::Left
	{
		switch (currentFrameIndex)
		{
		case 0:
			newPosition = base::Vector2{ playerBbox.right - 1, playerBbox.top + 14 };
			break;
		case 1:
			newPosition = base::Vector2{ playerBbox.right, playerBbox.top + 9 };
			break;
		case 2:
			newPosition = base::Vector2{ playerBbox.left - whipBbox.Width() - 8, playerBbox.top + 26 - whipBbox.Height() };
			break;
		default:
			newPosition = base::Vector2::Zero();
			break;
		}
	}

	parent.SetPosition(newPosition);
}
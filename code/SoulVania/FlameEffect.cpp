#include "stdafx.h"
#include "FlameEffect.h"

FlameEffect::FlameEffect(std::shared_ptr<AnimationFactory> flameAnimation)
{
	flame = std::make_unique<AnimatedSprite>(flameAnimation);
	isFinished = true;
}

void FlameEffect::Show(base::Vector2 position)
{
	auto flameRect = flame->GetTextureRegion().GetFrameRectangle();

	this->position = base::Vector2{
		position.x - flameRect.Width() / 2,
		position.y - flameRect.Height() / 2 };

	isFinished = false;
}

bool FlameEffect::IsFinished()
{
	return isFinished;
}

void FlameEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	flame->Update();

	if (flame->AnimateComplete())
		isFinished = true;
}

void FlameEffect::Draw(SpriteExtensions& spriteBatch)
{
	spriteBatch.Draw(*flame, position);
}
#pragma once

#include "IEffect.h"
#include "AnimatedSprite.h"

class FlameEffect : public IEffect
{
public:
	FlameEffect(std::shared_ptr<AnimationFactory> flameAnimation);

	void Show(base::Vector2 position) override;
	bool IsFinished() override;

	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	bool isFinished;
	base::Vector2 position;
	std::unique_ptr<AnimatedSprite> flame;
};
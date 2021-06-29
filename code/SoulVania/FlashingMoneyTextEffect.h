#pragma once

#include "IEffect.h"
#include "AnimatedSprite.h"
#include "Stopwatch.h"

class FlashingMoneyTextEffect : public IEffect
{
public:
	FlashingMoneyTextEffect(std::shared_ptr<AnimationFactory> moneyTextAnimation);

	void Show(base::Vector2 position) override;
	bool IsFinished() override;

	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	bool isFinished;
	base::Vector2 position;
	std::unique_ptr<AnimatedSprite> moneyText;

	Stopwatch lifespanTimer;
};
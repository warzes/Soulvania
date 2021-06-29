#pragma once

#include "IEffect.h"
#include "Sprite.h"
#include "Stopwatch.h"

class WaterEffect : public IEffect
{
public:
	WaterEffect(std::shared_ptr<Texture> waterTexture);

	void Show(base::Vector2 position) override;
	bool IsFinished() override;

	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	bool isFinished;

	base::Vector2 dropletLeftVelocity;
	base::Vector2 dropletTopVelocity;
	base::Vector2 dropletRightVelocity;

	base::Vector2 dropletLeftPosition;
	base::Vector2 dropletTopPosition;
	base::Vector2 dropletRightPosition;

	std::unique_ptr<Sprite> water;
	Stopwatch lifespanTimer;
};
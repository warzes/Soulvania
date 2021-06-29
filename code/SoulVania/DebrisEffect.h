#pragma once

#include "IEffect.h"
#include "Sprite.h"
#include "Stopwatch.h"

class DebrisEffect : public IEffect
{
public:
	DebrisEffect(std::shared_ptr<Texture> debrisTexture);

	void Show(base::Vector2 position) override;
	bool IsFinished() override;

	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	bool isFinished;

	base::Vector2 debrisTopLeftVelocity;
	base::Vector2 debrisTopRightVelocity;
	base::Vector2 debrisBottomLeftVelocity;
	base::Vector2 debrisBottomRightVelocity;

	base::Vector2 debrisTopLeftPosition;
	base::Vector2 debrisTopRightPosition;
	base::Vector2 debrisBottomLeftPosition;
	base::Vector2 debrisBottomRightPosition;

	std::unique_ptr<Sprite> debris;
	Stopwatch lifespanTimer;
};
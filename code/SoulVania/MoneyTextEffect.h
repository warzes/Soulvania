#pragma once

#include "IEffect.h"
#include "Sprite.h"
#include "Stopwatch.h"

class MoneyTextEffect : public IEffect
{
public:
	MoneyTextEffect(std::shared_ptr<Texture> moneyTextTexture);

	void Show(base::Vector2 position) override;
	bool IsFinished() override;

	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	bool isFinished;
	base::Vector2 position;
	std::unique_ptr<Sprite> moneyText;

	Stopwatch lifespanTimer;
};
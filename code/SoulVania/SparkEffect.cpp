#include "stdafx.h"
#include "SparkEffect.h"

constexpr auto SPARK_LIFESPAN = 140;

SparkEffect::SparkEffect(std::shared_ptr<Texture> sparkTexture)
{
	spark = std::make_unique<Sprite>(sparkTexture);
	isFinished = true;
}

void SparkEffect::Show(base::Vector2 position)
{
	auto sparkRect = spark->GetTextureRegion().GetFrameRectangle();

	this->position = base::Vector2{
		position.x - sparkRect.Width() - 4,
		position.y - sparkRect.Height() - 4 };

	sparkLifespanTimer.Start();
	isFinished = false;
}

bool SparkEffect::IsFinished()
{
	return isFinished;
}

void SparkEffect::Update(GameTime gameTime)
{
	if (sparkLifespanTimer.ElapsedMilliseconds() > SPARK_LIFESPAN)
	{
		isFinished = true;
		sparkLifespanTimer.Reset();
	}
}

void SparkEffect::Draw(SpriteExtensions& spriteBatch)
{
	if (!IsFinished())
		spriteBatch.Draw(*spark, position);
}
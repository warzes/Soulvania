#pragma once

#include "TextureRegion.h"
#include "Color.h"
#include <raylib/raylib.h>

enum class SpriteEffects
{
	None,
	FlipHorizontally,
	FlipVertically,
};

class Sprite
{
public:
	Sprite(std::shared_ptr<Texture> texture);
	Sprite(TextureRegion textureRegion);

	void SetTextureRegion(TextureRegion textureRegion);
	TextureRegion GetTextureRegion();

	RectF GetFrameRectangle(base::Vector2 position);
	RectF GetBoundingRectangle(base::Vector2 position);

	void SetAlpha(float alpha);
	float GetAlpha();

	void SetColor(base::Color color);
	base::Color GetColor();

	void SetVisibility(bool isVisible);
	bool IsVisible();

	void SetEffect(SpriteEffects effect);
	SpriteEffects GetEffect();

private:
	TextureRegion textureRegion;

	float alpha;
	base::Color color = base::Color::White();
	bool isVisible;
	SpriteEffects effect;
};
#pragma once

#include "SpriteBatch.h"
#include "Transform.h"


class SpriteExtensions : public SpriteBatch
{
public:
	using SpriteBatch::Draw;

	void Draw(Sprite sprite, base::Vector2 position, bool useViewport = true);
	void Draw(Sprite sprite, base::Transform transform, bool useViewport = true);
	void Draw(Sprite sprite, base::Vector2 position, float rotation, base::Vector2 scale, bool useViewport = true);
};
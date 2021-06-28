#pragma once

#include "Sprite.h"
#include "Vector2.h"
#include "Color.h"

class SpriteBatch
{
public:
	void Begin(unsigned long flags);
	void End();

	void Draw(Texture& texture, base::Vector2 position, base::Color color, bool useViewport = true);
	void Draw(
		Texture& texture,
		base::Vector2 position,
		Rect* rectangle,
		base::Color color,
		float rotation,
		base::Vector2 scale,
		SpriteEffects effects,
		bool useViewport = true);

	void DrawString(Font& spriteFont, const std::string& text, base::Vector2 position, base::Color color, bool useViewport = true);
};
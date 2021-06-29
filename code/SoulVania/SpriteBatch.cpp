#include "stdafx.h"
#include "SpriteBatch.h"

void SpriteBatch::Begin(unsigned long flag)
{
}

void SpriteBatch::End()
{
}

void SpriteBatch::Draw(Texture& texture, base::Vector2 position, base::Color color, bool useViewport)
{
	Draw(texture, position, nullptr, color, 0.0f, base::Vector2::One(), SpriteEffects::None, useViewport);
}

void SpriteBatch::Draw(
	Texture& texture,
	base::Vector2 position,
	Rect* rectPtr,
	base::Color color,
	float rotation,
	base::Vector2 scale,
	SpriteEffects effects,
	bool useViewport)
{
	auto source = Rectangle{};
	if (rectPtr == nullptr) // if null, draws full texture
		source = Rectangle{ 0, 0, (float)texture.width, (float)texture.height };
	else
		source = Rectangle{ (float)rectPtr->left, (float)rectPtr->top, (float)rectPtr->right, (float)rectPtr->bottom };

	auto scaleVec = base::Vector2{};
	if (effects == SpriteEffects::FlipHorizontally)
		scaleVec = base::Vector2{ -1, 1 } *scale;
	else if (effects == SpriteEffects::FlipVertically)
		scaleVec = base::Vector2{ 1, -1 } *scale;
	else // SpriteEffects::None
		scaleVec = base::Vector2{ 1, 1 } *scale;

	Rectangle dest = { position.x, position.y, source.width * scaleVec.x, source.height * scaleVec.y };
	Vector2 origin = { 0.0f, 0.0f };
	Color clr = { (unsigned char)color.R(), (unsigned char)color.G(), (unsigned char)color.B(), 255 };

	DrawTexturePro(texture, source, dest, origin, rotation, clr);
}

void SpriteBatch::DrawString(Font& spriteFont, const std::string& text, base::Vector2 position, base::Color color, bool useViewport)
{
	Color clr = { (unsigned char)color.R(), (unsigned char)color.G(), (unsigned char)color.B(), 255 };
	DrawTextEx(spriteFont, text.c_str(), Vector2 { position.x, position.y }, (float)spriteFont.baseSize, 1, clr);
}
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
	auto rect = Rect{};
	if (rectPtr == nullptr) // if null, draws full texture
		rect = Rect{ 0, 0, texture.width, texture.height };
	else
		rect = *rectPtr;

	auto scaleVec = base::Vector2{};
	if (effects == SpriteEffects::FlipHorizontally)
		scaleVec = base::Vector2{ -1, 1 } *scale;
	else if (effects == SpriteEffects::FlipVertically)
		scaleVec = base::Vector2{ 1, -1 } *scale;
	else // SpriteEffects::None
		scaleVec = base::Vector2{ 1, 1 } *scale;

	//if (useViewport)
	//	position = graphicsDevice.GetViewport().Project(position);
	//auto center = Vector2{ position.x + rect.Width() / 2, position.y + rect.Height() / 2 };

	//auto oldMatrix = Matrix{};
	//auto newMatrix = Matrix{};

	//spriteHandler->GetTransform(&oldMatrix);
	//D3DXMatrixTransformation2D(
	//	&newMatrix, // the result matrix
	//	&center,    // scaling center vector
	//	0.0f,       // scaling rotation value
	//	&scaleVec,  // scaling vector
	//	&center,    // rotating center/pivot vector
	//	rotation,   // rotating angle (radians)
	//	nullptr     // translating vector
	//);

	//spriteHandler->SetTransform(&newMatrix);
	//spriteHandler->Draw(texture.Get(), &rect, nullptr, &Vector3{ position }, color.Get());
	//spriteHandler->SetTransform(&oldMatrix);
}

void SpriteBatch::DrawString(Font& spriteFont, const std::string& text, base::Vector2 position, base::Color color, bool useViewport)
{
	//auto textSize = spriteFont.MessureString(text);
	//auto rect = Rect{};

	//if (useViewport)
	//	position = graphicsDevice.GetViewport().Project(position);

	//auto x = (int)position.x;
	//auto y = (int)position.y;
	//auto textWidth = (int)textSize.x;
	//auto textHeight = (int)textSize.y;

	//rect.left = x;
	//rect.top = y;
	//rect.right = x + textWidth;
	//rect.bottom = y + textHeight;

	//font->DrawTextA(spriteHandler, text.c_str(), -1, &rect, DT_LEFT, color.Get());
}
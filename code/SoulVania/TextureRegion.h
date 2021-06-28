#pragma once

#include "Rect.h"
#include "RectF.h"
#include <raylib/raylib.h>

class TextureRegion
{
public:
	TextureRegion(std::shared_ptr<Texture> texture);
	TextureRegion(std::shared_ptr<Texture> texture, Rect frame);
	TextureRegion(std::shared_ptr<Texture> texture, Rect frame, RectF boundary);

	Texture& GetTexture();
	Rect GetFrameRectangle();
	RectF GetBoundingRectangle();

private:
	std::shared_ptr<Texture> texture;
	Rect frame; // used to draw
	RectF boundary; // used to detect collision
};
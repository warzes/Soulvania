#pragma once

#include "Sprite.h"

class Tile
{
public:
	Tile(Sprite sprite, RectF boundingBox);

	Sprite& GetSprite();
	RectF GetBoundingBox();

private:
	Sprite sprite;
	RectF boundingBox;
};
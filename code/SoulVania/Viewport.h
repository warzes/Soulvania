#pragma once

#include "Vector2.h"
#include "RectF.h"

struct Viewport
{
	float x;
	float y;
	int width;
	int height;

	base::Vector2 Project(float x, float y);

	// Get position relative to screen space from world space position
	base::Vector2 Project(base::Vector2 source);

	// Get position relative to world space from screen space position
	base::Vector2 Unproject(base::Vector2 source);

	RectF Bounds();
};
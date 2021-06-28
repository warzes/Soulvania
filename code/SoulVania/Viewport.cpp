#include "stdafx.h"
#include "Viewport.h"

base::Vector2 Viewport::Project(float x, float y)
{
	return Project(base::Vector2{ x, y });
}

base::Vector2 Viewport::Project(base::Vector2 source)
{
	auto viewport_x = roundf(x);
	auto viewport_y = roundf(y);

	return base::Vector2{
		source.x - viewport_x,
		source.y - viewport_y };
}

base::Vector2 Viewport::Unproject(base::Vector2 source)
{
	auto viewport_x = roundf(x);
	auto viewport_y = roundf(y);

	return base::Vector2{
		source.x + viewport_x,
		source.y + viewport_y };
}

RectF Viewport::Bounds()
{
	return RectF{ x, y, (float)width, (float)height };
}
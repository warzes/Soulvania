#pragma once

#include "Vector2.h"
#include "Rect.h"

// A rectangle but store value in float, is used to calculate bounding box for
// real-time collision detection
struct RectF
{
	float left;
	float top;
	float right;
	float bottom;

	RectF();
	RectF(float left, float top, float width, float height);

	float X();
	float Y();
	float Width();
	float Height();

	base::Vector2 GetPosition();
	static RectF Empty();

	bool operator==(RectF other);
	bool operator!=(RectF other);
	bool Contains(RectF value);
	bool Contains(base::Vector2 value);
	bool Intersects(RectF value);
	bool TouchesOrIntersects(RectF value);

	static RectF Merge(RectF value1, RectF value2);
	static std::vector<RectF> Split(RectF origin, float childWidth, float childHeight);

	explicit operator Rect();
};
#pragma once

// TODO: заменить на raylib::Vector2

namespace base
{

	struct Vector2
	{
		Vector2();
		Vector2(float x, float y);

		static Vector2 Zero();
		static Vector2 One();

		Vector2 operator*(const Vector2& value) const;
		Vector2 operator+(const Vector2& value) const;
		Vector2 operator-(const Vector2& value) const;
		Vector2 operator+(const float value) const;
		Vector2 operator-(const float value) const;
		Vector2 operator*(const float value) const;
		Vector2 operator/(const float value) const;

		static float Distance(Vector2 value1, Vector2 value2);
		float Length();
		static Vector2 Normalize(Vector2 value);

		float x, y;
	};
}
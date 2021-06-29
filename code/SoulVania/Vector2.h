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

		bool operator==(const Vector2& rhs) const noexcept { return x == rhs.x && y == rhs.y; }
		bool operator!=(const Vector2& rhs) const noexcept { return x != rhs.x || y != rhs.y; }

		Vector2 operator+(const float rhs) const noexcept { return { x + rhs, y + rhs }; }
		Vector2 operator+(const Vector2& rhs) const noexcept { return { x + rhs.x, y + rhs.y }; }
		Vector2 operator-() const noexcept { return { -x, -y }; }
		Vector2 operator-(const float rhs) const noexcept { return { x - rhs, y - rhs }; }
		Vector2 operator-(const Vector2& rhs) const noexcept { return { x - rhs.x, y - rhs.y }; }
		Vector2 operator*(const float rhs) const noexcept { return { x * rhs, y * rhs }; }
		Vector2 operator*(const Vector2& rhs) const noexcept { return { x * rhs.x, y * rhs.y }; }
		Vector2 operator/(const float rhs) const { return { x / rhs, y / rhs }; }
		Vector2 operator/(const Vector2& rhs) const { return { x / rhs.x, y / rhs.y }; }

		Vector2& operator+=(const Vector2& rhs) noexcept
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vector2& operator-=(const Vector2& rhs) noexcept
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Vector2& operator*=(const float rhs) noexcept
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}

		Vector2& operator*=(const Vector2& rhs) noexcept
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		Vector2& operator/=(const float rhs)
		{
			const float invRhs = 1.0f / rhs;
			x *= invRhs;
			y *= invRhs;
			return *this;
		}

		Vector2& operator/=(const Vector2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		static float Distance(Vector2 value1, Vector2 value2);
		float Length();
		static Vector2 Normalize(Vector2 value);

		float x, y;
	};
}
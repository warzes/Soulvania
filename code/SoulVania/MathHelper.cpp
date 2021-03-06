#include "stdafx.h"
#include "MathHelper.h"

#define PI 3.14159265358979323846f

double const MathHelper::TWO_PI = PI * 2.0f;
double const MathHelper::PI_180 = PI / 180.0f;

float MathHelper::Lerp(float value1, float value2, float amount)
{
	return value1 + (value2 - value1) * amount;
}

float MathHelper::ToRadians(float degrees)
{
	return (float)(degrees * PI_180); // 1 degree = pi / 180 radians
}

base::Vector2 MathHelper::Degrees2Vector(float degrees)
{
	auto radian = ToRadians(degrees);
	auto x = std::cos(radian);
	auto y = std::sin(radian);

	return base::Vector2{ x, y };
}

base::Vector2 MathHelper::RandomDirection(float minAngle, float maxAngle)
{
	auto angle = RandomBetween(ToRadians(minAngle), ToRadians(maxAngle));
	auto x = (float)std::cos(angle);
	auto y = (float)std::sin(angle);

	return base::Vector2{ x, y };
}

bool MathHelper::RandomBoolean()
{
	return rand() % 2 == 0 ? true : false;
}

bool MathHelper::RandomPercent(float percentValue)
{
	return RandomBetween(1, 100) <= percentValue;
}

int MathHelper::RandomBetween(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float MathHelper::RandomBetween(float min, float max)
{
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random*range) + min;
}

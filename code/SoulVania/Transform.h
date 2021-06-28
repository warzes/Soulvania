#pragma once

#include "Vector2.h"

namespace base
{
	struct Transform
	{
		Vector2 position;
		float rotation;
		Vector2 scale = Vector2::One();
	};
}
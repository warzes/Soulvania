#pragma once

#include "Direction.h"

enum class Facing
{
	Right,
	Left,
	None,
};

Facing Opposite(Facing facing);
Facing Direction2Facing(Direction direction);
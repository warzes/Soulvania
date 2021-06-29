#include "stdafx.h"
#include "Facing.h"

Facing Opposite(Facing facing)
{
	if (facing == Facing::Left)
		return Facing::Right;
	else
		return Facing::Left;
}

Facing Direction2Facing(Direction direction)
{
	switch (direction)
	{
	case Direction::Left:
		return Facing::Left;

	case Direction::Right:
		return Facing::Right;

	default:
		return Facing::None;
	}
}

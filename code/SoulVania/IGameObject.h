#pragma once

#include "Body.h"

class IGameObject : public IColliable
{
public:
	virtual Body& GetBody() = 0;
};
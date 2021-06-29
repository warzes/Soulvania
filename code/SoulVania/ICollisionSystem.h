#pragma once

#include "IReceiver.h"

struct UpdateData;

class ICollisionSystem : public IReceiver
{
public:
	virtual void Update(UpdateData& updateData) = 0;
	virtual ~ICollisionSystem() {}
};
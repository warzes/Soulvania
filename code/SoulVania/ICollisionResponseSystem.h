#pragma once

#include "IReceiver.h"

struct UpdateData;

class ICollisionResponseSystem : public IReceiver
{
public:
	virtual void Update(UpdateData& updateData) = 0;
	virtual ~ICollisionResponseSystem() {}
};
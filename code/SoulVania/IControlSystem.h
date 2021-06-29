#pragma once

#include "IReceiver.h"

struct UpdateData;

class IControlSystem : public IReceiver
{
public:
	virtual void Enabled(bool value) = 0;
	virtual bool Enabled() = 0;

	virtual void Update(UpdateData& updateData) = 0;
	virtual ~IControlSystem() {}
};
#pragma once

#include "IControlSystem.h"

class ControlSystem : public IControlSystem
{
public:
	ControlSystem();

	void Enabled(bool value) override;
	bool Enabled() override;

	virtual void Receive(int message) override {};
	virtual void Update(UpdateData& updateData) {};

protected:
	bool enabled;
};
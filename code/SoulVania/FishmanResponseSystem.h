#pragma once

#include "ResponseSystem.h"
#include "Fishman.h"

class FishmanResponseSystem : public ResponseSystem
{
public:
	FishmanResponseSystem(Fishman& parent);

	GameObject& GetParent() override;
	void Update(UpdateData& updateData) override;

protected:
	Fishman& parent;
	bool wasOnGround;
};
#pragma once

#include "ResponseSystem.h"
#include "Panther.h"

class PantherResponseSystem : public ResponseSystem
{
public:
	PantherResponseSystem(Panther& parent);
	GameObject& GetParent() override;

private:
	Panther& parent;

	void OnTouchingGround(CollisionData collisionData) override;
	void OnFalling() override;
	void OnLanding() override;
};
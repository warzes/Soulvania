#pragma once

#include "ResponseSystem.h"
#include "Zombie.h"

class ZombieResponseSystem : public ResponseSystem
{
public:
	ZombieResponseSystem(Zombie& parent);
	GameObject& GetParent() override;

protected:
	Zombie& parent;

	void OnTouchingGround(CollisionData collisionData) override;
	void OnFalling() override;
	void OnLanding() override;
};
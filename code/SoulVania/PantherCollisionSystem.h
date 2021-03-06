#pragma once

#include "CollisionSystem.h"

class Panther;

// Only check for collision with static object (wall, floor, platform)
class PantherCollisionSystem : public CollisionSystem
{
public:
	PantherCollisionSystem(Panther& parent);

	IGameObject& GetParent() override;
	void Update(UpdateData& updateData) override;

private:
	Panther& parent;
};
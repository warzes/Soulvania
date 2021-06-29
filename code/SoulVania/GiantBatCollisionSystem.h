#pragma once

#include "Rect.h"
#include "CollisionSystem.h"

class GiantBat;

// Only check for collision with static object (wall, floor, platform)
class GiantBatCollisionSystem : public CollisionSystem
{
public:
	GiantBatCollisionSystem(GiantBat& parent);

	IGameObject& GetParent() override;
	void Update(UpdateData& updateData) override;

private:
	GiantBat& parent;

	void CheckZonesCollision(Rect playerBbox);

	bool wasPlayerInAttackZone;
	bool wasPlayerInThreatZone;
};
#pragma once

#include "ICollisionSystem.h"
#include "GameObject.h"

class AreaCollisionSystem : public ICollisionSystem
{
public:
	AreaCollisionSystem(GameObject& parent);

	void Receive(int message) override {};
	void Update(UpdateData& updateData) override;

protected:
	GameObject& parent;
	bool wasPlayerInSpawnZone;
};
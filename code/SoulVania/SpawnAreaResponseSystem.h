#pragma once

#include "ICollisionResponseSystem.h"
#include "SpawnArea.h"

class Player;

class SpawnAreaResponseSystem : public ICollisionResponseSystem
{
public:
	SpawnAreaResponseSystem(SpawnArea& parent);

	void Receive(int message) override;
	void Update(UpdateData& updateData) override;

private:
	SpawnArea& parent;
};
#pragma once

#include "SpawnArea.h"

class VampireBatSpawnArea : public SpawnArea
{
public:
	VampireBatSpawnArea(ObjectFactory& objectFactory);

	void SetGroupSpawnTime(int groupSpawnTime) override;

private:
	int originalGroupSpawnTime;

	void SpawnObject(UpdateData& updateData) override;
};
#pragma once

#include "SpawnArea.h"

class ZombieSpawnArea : public SpawnArea
{
public:
	ZombieSpawnArea(ObjectFactory& objectFactory);

private:
	void SpawnObject(UpdateData& updateData) override;
};
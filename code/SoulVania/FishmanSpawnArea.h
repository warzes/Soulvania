#pragma once

#include "SpawnArea.h"

class FishmanSpawnArea : public SpawnArea
{
public:
	FishmanSpawnArea(ObjectFactory& objectFactory);

private:
	void SpawnObject(UpdateData& updateData) override;
};
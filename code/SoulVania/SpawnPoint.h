#pragma once

#include "ISpawner.h"
#include "GameObject.h"

class ObjectFactory;

class SpawnPoint : public GameObject, public ISpawner
{
public:
	SpawnPoint(ObjectId spawnObjectType, ObjectFactory& objectFactory);

	SpawnState GetSpawnState() override;
	void Update(UpdateData& updateData) override;

private:
	ObjectFactory& objectFactory;
	ObjectId spawnObjectType;
	SpawnState spawnState;

	void Activate() override;
	void Deactivate() override;
};
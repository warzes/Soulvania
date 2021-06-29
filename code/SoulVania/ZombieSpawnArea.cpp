#include "stdafx.h"
#include "ZombieSpawnArea.h"
#include "MathHelper.h"
#include "ObjectFactory.h"
#include "CollisionGrid.h"

ZombieSpawnArea::ZombieSpawnArea(ObjectFactory& objectFactory) :
	SpawnArea{ ObjectId::Zombie, objectFactory }
{
}

void ZombieSpawnArea::SpawnObject(UpdateData& updateData)
{
	auto viewport = updateData.viewport;
	auto object = objectFactory.CreateEnemy(spawnObjectType);
	auto spawnPosition = base::Vector2{};
	auto facing = Facing{};

	if (MathHelper::RandomPercent(directionChances[Direction::Right]))
	{
		spawnPosition.x = viewport.right - object->GetFrameRect().Width();
		facing = Facing::Left;
	}
	else
	{
		spawnPosition.x = viewport.left;
		facing = Facing::Right;
	}

	// -1: to make object barely hit the ground or it will fall through it
	spawnPosition.y = GetBoundingBox().bottom - object->GetFrameRect().Height() - 1;
	object->SetPosition(spawnPosition);
	object->SetFacing(facing);

	collisionGrid->Add(std::move(object), CollisionObjectType::Entity);
}
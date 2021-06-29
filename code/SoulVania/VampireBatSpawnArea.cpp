#include "stdafx.h"
#include "VampireBatSpawnArea.h"
#include "MathHelper.h"
#include "ObjectFactory.h"
#include "CollisionGrid.h"

VampireBatSpawnArea::VampireBatSpawnArea(ObjectFactory &objectFactory) :
	SpawnArea{ ObjectId::VampireBat, objectFactory }
{
}

void VampireBatSpawnArea::SetGroupSpawnTime(int groupSpawnTime)
{
	this->originalGroupSpawnTime = groupSpawnTime;
	this->groupSpawnTime = originalGroupSpawnTime;
}

void VampireBatSpawnArea::SpawnObject(UpdateData &updateData)
{
	if (spawnGroupCount == 1) // Randomize groupSpawnTime before resetting group spawn timer
	{
		// In the original game, sometimes bat spawn time is much shorter than other times
		if (MathHelper::RandomPercent(20))
			groupSpawnTime = originalGroupSpawnTime / 3;
		else
			groupSpawnTime = originalGroupSpawnTime;
	}

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

	auto playerBbox = updateData.player->GetBoundingBox();
	spawnPosition.y = playerBbox.bottom - playerBbox.Height() / 2 - object->GetFrameRect().Height() / 2;

	object->SetPosition(spawnPosition);
	object->SetFacing(facing);

	collisionGrid->Add(std::move(object), CollisionObjectType::Entity);
}

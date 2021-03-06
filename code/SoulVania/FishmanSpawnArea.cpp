#include "stdafx.h"
#include "FishmanSpawnArea.h"
#include "MathHelper.h"
#include "UpdateData.h"
#include "Fishman.h"
#include "ObjectFactory.h"
#include "CollisionGrid.h"

constexpr auto MIN_OFFSET = 64;
constexpr auto MAX_OFFSET = 224;
constexpr auto MAX_FISHMAN_COUNT = 2;

FishmanSpawnArea::FishmanSpawnArea(ObjectFactory& objectFactory) :
	SpawnArea{ ObjectId::Fishman, objectFactory }
{
}

void FishmanSpawnArea::SpawnObject(UpdateData& updateData)
{
	auto currentFishmanCount = 0;

	collisionGrid->GetCellsFromBoundingBox(updateData.viewport, [&](CollisionCell& cell, int col, int row)
		{
			auto& entities = cell.GetEntites();

			for (auto& entity : entities)
			{
				if (entity->GetId() == ObjectId::Fishman)
					currentFishmanCount++;
			}
		});

	if (currentFishmanCount >= MAX_FISHMAN_COUNT)
		return;

	auto viewport = updateData.viewport;
	auto object = objectFactory.CreateEnemy(spawnObjectType);
	auto facing = Facing{};
	auto playerBbox = updateData.player->GetBoundingBox();
	auto randomOffset = MathHelper::RandomBetween(MIN_OFFSET, MAX_OFFSET);

	if (playerBbox.right + randomOffset >= viewport.right - object->GetFrameRect().Width())
		facing = Facing::Right;
	else if (playerBbox.left - randomOffset <= viewport.left)
		facing = Facing::Left;
	else
		facing = MathHelper::RandomBoolean() ? Facing::Left : Facing::Right;

	auto spawnPosition = base::Vector2{};

	if (facing == Facing::Left)
		spawnPosition.x = playerBbox.right + randomOffset;
	else // facing == Facing::Right
		spawnPosition.x = playerBbox.left - randomOffset;

	spawnPosition.y = GetBoundingBox().bottom - object->GetFrameRect().Height();
	object->SetPosition(spawnPosition);
	object->SetFacing(facing);
	static_cast<Fishman&>(*object).Launch();

	collisionGrid->Add(std::move(object), CollisionObjectType::Entity);
}
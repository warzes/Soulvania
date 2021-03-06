#include "stdafx.h"
#include "StandardCollisionSystem.h"
#include "GameObject.h"
#include "UpdateData.h"

StandardCollisionSystem::StandardCollisionSystem(GameObject& parent) : parent{ parent }
{
}

IGameObject& StandardCollisionSystem::GetParent()
{
	return parent;
}

void StandardCollisionSystem::Update(UpdateData& updateData)
{
	auto& body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto collisionObjects = *updateData.collisionObjects;

	for (auto& collisionObject : collisionObjects)
	{
		CalculateCollision(*collisionObject, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollisionResults(results));
}

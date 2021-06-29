#include "stdafx.h"
#include "HolyWaterResponseSystem.h"
#include "Player.h"
#include "UpdateData.h"
#include "Container.h"
#include "Enemy.h"

HolyWaterResponseSystem::HolyWaterResponseSystem(HolyWater& parent) :
	PoisonResponseSystem{ parent },
	parent{ parent }
{
}

void HolyWaterResponseSystem::Update(UpdateData& updateData)
{
	PoisonResponseSystem::Update(updateData);

	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto objectId = (ObjectId)result.collidedObject.GetType();

		switch (objectId)
		{
		case ObjectId::Block:
		{
			if (parent.IsFlaming())
				break;

			auto& block = dynamic_cast<GameObject&>(result.collidedObject);
			auto position = parent.GetPosition();

			if (result.direction == Direction::Top)
			{
				position.y = block.GetPosition().y - parent.GetFrameRect().Height();
				parent.SetPosition(position);
			}

			parent.StartFlaming();
			break;
		}
		}
	}
}
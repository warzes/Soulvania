#include "stdafx.h"
#include "ResponseSystem.h"
#include "UpdateData.h"
#include "GameObject.h"
#include "Settings.h"

ResponseSystem::ResponseSystem()
{
	wasOnGround = false;
}

GameObject& ResponseSystem::GetParent()
{
	return GameObject::NullObject();
}

void ResponseSystem::Update(UpdateData& updateData)
{
	auto collisionData = GetParent().GetBody().GetCollisionData();
	auto isOnGround = false;

	for (auto result : collisionData.collisionResults)
	{
		auto objectId = (ObjectId)result.collidedObject.GetType();

		switch (objectId)
		{
		case ObjectId::Block:
		case ObjectId::BreakableBlock:
		{
			if (result.direction != Direction::Top)
				break;

			OnTouchingGround(collisionData);

			isOnGround = true;
			break;
		}
		}
	}

	if (wasOnGround != isOnGround)
	{
		if (wasOnGround)
			OnFalling();
		else
			OnLanding();

		wasOnGround = isOnGround;
	}
}

void ResponseSystem::OnTouchingGround(CollisionData collisionData)
{
}

void ResponseSystem::OnFalling()
{
}

void ResponseSystem::OnLanding()
{
}

void ResponseSystem::ClampDistance_X(CollisionData collisionData)
{
	auto distance = GetParent().GetDistance();
	auto time = collisionData.minTime;
	auto normal = collisionData.minNormal;

	// *0.4f : need to push out a bit to avoid overlapping next frame
	distance.x = distance.x * time.x + normal.x * 0.4f;
	GetParent().SetDistance(distance);
}

void ResponseSystem::ClampDistance_Y(CollisionData collisionData)
{
	auto distance = GetParent().GetDistance();
	auto time = collisionData.minTime;
	auto normal = collisionData.minNormal;

	distance.y = distance.y * time.y + normal.y * 0.4f;
	GetParent().SetDistance(distance);
}
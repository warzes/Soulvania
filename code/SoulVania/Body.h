#pragma once

#include "CollisionData.h"
#include "BoxCollisionResult.h"

class Body
{
public:
	Body(IColliable& colliableObject);

	CollisionData GetCollisionData();
	void SetCollisionData(CollisionData collisionData);
	void ClearCollisionData();

	bool Enabled();
	void Enabled(bool value);

	BoxCollisionResult PredictCollision(RectF& staticRect);
	CollisionResult PredictCollision(IColliable& staticObject);

private:
	struct SweptAABBResult;

	using BroadPhase = RectF;

	IColliable& parent;
	CollisionData collisionData;
	bool enabled;

	SweptAABBResult SweptAABB(RectF movingRect, base::Vector2 distance, RectF staticRect);
	BroadPhase CreateBroadPhase(RectF rect, base::Vector2 distance);
};
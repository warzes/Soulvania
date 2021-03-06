#pragma once

#include "CollisionData.h"
#include "ICollisionSystem.h"

class IGameObject;

// A collision detection system using Swept AABB algorithm for dynamic objects
class CollisionSystem : public ICollisionSystem
{
public:
	virtual IGameObject& GetParent();
	virtual void Receive(int message) override {};

	virtual void Update(UpdateData& updateData) override = 0;

protected:
	void CalculateCollision(IGameObject& gameObject, CollisionResults& results);
	// Use simple rectangle intersect check to calculate collision between two static objects
	bool CalculateStaticCollision(IGameObject& gameObject, CollisionResults& results);
	// Use Swept AABB algorithm to calculate collision between a dynamic object with another object
	bool CalculateDynamicCollision(IGameObject& gameObject, CollisionResults& results);

	CollisionData FilterCollisionResults(CollisionResults collisionResults);
};
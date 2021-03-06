#pragma once

#include "CollisionSystem.h"

class GameObject;

// A collision detection system for static objects only
class SimpleCollisionSystem : public CollisionSystem
{
public:
	SimpleCollisionSystem(GameObject& parent);

	IGameObject& GetParent() override;
	void Update(UpdateData& updateData) override;

private:
	IGameObject& parent;
};
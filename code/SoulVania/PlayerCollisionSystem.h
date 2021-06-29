#pragma once

#include "CollisionSystem.h"

class GameObject;

class PlayerCollisionSystem : public CollisionSystem
{
public:
	PlayerCollisionSystem(GameObject& parent);

	IGameObject& GetParent() override;
	void Update(UpdateData& updateData) override;

private:
	IGameObject& parent;
};
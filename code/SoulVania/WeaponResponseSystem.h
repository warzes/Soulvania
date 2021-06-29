#pragma once

#include "ICollisionResponseSystem.h"
#include "Player.h"

class Enemy;

class WeaponResponseSystem : public ICollisionResponseSystem
{
public:
	WeaponResponseSystem(GameObject& parent, bool destroyOnHit);

	virtual void Receive(int message) override;
	void Update(UpdateData& updateData) override;

private:
	GameObject& parent;
	std::vector<GameObject*> hitObjects;
	bool destroyOnHit;

	void OnCollideWithContainer(CollisionResult& result);
	void OnCollideWithBreakableWall(CollisionResult& result);
	void OnCollideWithEnemy(CollisionResult& result, Player& player);
	void OnCollideWithFireball(CollisionResult& result);
};
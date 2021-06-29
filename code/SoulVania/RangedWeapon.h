#pragma once

#include "GameObject.h"
#include "IAttackable.h"

// Throwable weapon like Dagger, Axe, Boomerang,...
class RangedWeapon : public GameObject, public IAttackable
{
public:
	RangedWeapon(ObjectId type);

	void SetThrowSoundEffect(std::string soundEffect);
	base::Vector2 GetThrowVelocity();
	void SetThrowVelocity(base::Vector2 velocity);
	int GetAttack() override;
	void SetAttack(int attack) override;

	void Update(UpdateData& updateData) override;
	void Throw(base::Vector2 position);

private:
	base::Vector2 throwVelocity;
	int attack;
	std::string throwSoundEffect;
};
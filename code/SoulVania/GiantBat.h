#pragma once

#include "Stopwatch.h"
#include "Enemy.h"
#include "IBoss.h"
#include "RangedWeapon.h"

enum class GiantBatState
{
	IDLE,
	HOVERING,
	FLYING,

	// When giant bat and simon is at the same height. It has to
	// rise itself quickly to make the diving attack viable
	RISING,

	DIVING,
	SHOOTING,
};

class GiantBat : public Enemy, public IBoss
{
public:
	GiantBat();

	float GetDiveSpeed();
	void SetDiveSpeed(float speed);
	void SetActive() override;
	bool IsInRange();
	void IsInRange(bool value);

	Rect GetAttackZone();
	void SetAttackZone(Rect attackZone);
	Rect GetThreatZone();
	void SetThreatZone(Rect threatZone);
	Rect GetMoveArea() override;
	void SetMoveArea(Rect moveArea) override;
	GiantBatState GetGiantBatState();

	void Update(UpdateData& updateData) override;

	void Idle();
	void Hover();
	void Fly(float distance);
	void Dive(base::Vector2 playerPosition);
	void Shoot(std::unique_ptr<RangedWeapon> fireball, base::Vector2 destination);

private:
	base::Vector2 playerPosition;
	float flyingDistance;
	float diveSpeed;
	bool isActive;
	bool isInRange;
	Rect attackZone; // If player is outside of attack zone, start shooting player
	Rect threatZone; // When player is inside threat zone, attack immediately
	Rect moveArea;
	GiantBatState giantBatState;

	void SetGiantBatState(GiantBatState state);
	void Rise();
	void DoDiveAttack();
	void ReleaseFireball();

	std::unique_ptr<RangedWeapon> fireball;
	Stopwatch shootingTimer;

	friend class GiantBatMovementSystem;
};
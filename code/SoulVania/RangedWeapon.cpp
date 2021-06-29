#include "stdafx.h"
#include "RangedWeapon.h"
#include "AudioManager.h"
#include "UpdateData.h"

RangedWeapon::RangedWeapon(ObjectId type) : GameObject{ type }
{
	this->throwVelocity = base::Vector2{ 500, 0 };
}

void RangedWeapon::SetThrowSoundEffect(std::string soundEffect)
{
	throwSoundEffect = soundEffect;
}

base::Vector2 RangedWeapon::GetThrowVelocity()
{
	return throwVelocity;
}

void RangedWeapon::SetThrowVelocity(base::Vector2 velocity)
{
	throwVelocity = velocity;
}

int RangedWeapon::GetAttack()
{
	return attack;
}

void RangedWeapon::SetAttack(int attack)
{
	this->attack = attack;
}

void RangedWeapon::Update(UpdateData& updateData)
{
	if (!updateData.isStopwatchActive)
		GameObject::Update(updateData);
	else
		if (renderingSystem != nullptr && state == ObjectState::DYING)
			renderingSystem->Update(updateData.gameTime); // Update hit effect

	auto viewport = updateData.viewport;

	if (!viewport.TouchesOrIntersects(GetFrameRect()))
		Destroy();
}

void RangedWeapon::Throw(base::Vector2 position)
{
	body.Enabled(true);
	SetVisibility(true);
	SetPosition(position);

	velocity = throwVelocity;

	if (facing == Facing::Right)
		velocity.x = std::abs(velocity.x);
	else
		velocity.x = -std::abs(velocity.x);

	AudioManager::Play(throwSoundEffect);
}
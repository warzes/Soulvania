#include "stdafx.h"
#include "HolyWater.h"
#include "Settings.h"
#include "AudioManager.h"

constexpr auto FLAMING_TIME = 1400;

HolyWater::HolyWater() : RangedWeapon{ ObjectId::HolyWater }
{
}

void HolyWater::StartFlaming()
{
	Detach<IMovementSystem>();
	isFlaming = true;
	SendMessageToSystems(MOVE_STATE_CHANGED);
	AudioManager::Play(SE_HOLY_WATER_TOUCHING_GROUND);
	flamingTimer.Start();
}

bool HolyWater::IsFlaming()
{
	return isFlaming;
}

void HolyWater::Update(UpdateData& updateData)
{
	RangedWeapon::Update(updateData);

	if (flamingTimer.ElapsedMilliseconds() >= FLAMING_TIME)
		Destroy();
}
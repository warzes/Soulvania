#include "stdafx.h"
#include "WaterArea.h"
#include "Settings.h"
#include "AudioManager.h"

WaterArea::WaterArea() : GameObject{ ObjectId::WaterArea }
{
}

void WaterArea::Splash(base::Vector2 position)
{
	splashPosition = position;
	SendMessageToSystems(OBJECT_HITS_WATER_SURFACE);
	AudioManager::Play(SE_HITTING_WATER_SURFACE);
}
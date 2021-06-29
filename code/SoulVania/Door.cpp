#include "stdafx.h"
#include "Door.h"
#include "AudioManager.h"
#include "Settings.h"

Door::Door() : GameObject{ ObjectId::Door }
{
}

DoorState Door::GetDoorState()
{
	return doorState;
}

void Door::Idle()
{
	doorState = DoorState::NORMAL;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Door::Open()
{
	doorState = DoorState::OPENING;
	AudioManager::Play(SE_USING_DOOR);
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Door::Close()
{
	doorState = DoorState::CLOSING;
	AudioManager::Play(SE_USING_DOOR);
	SendMessageToSystems(MOVE_STATE_CHANGED);
}
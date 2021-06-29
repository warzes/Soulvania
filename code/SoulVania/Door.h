#pragma once

#include "GameObject.h"

enum class DoorState
{
	NORMAL,
	OPENING,
	CLOSING,
};

class Door : public GameObject
{
public:
	Door();

	DoorState GetDoorState();
	void Idle();
	void Open();
	void Close();

private:
	DoorState doorState;
};
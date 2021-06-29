#pragma once

#include "Player.h"
#include "ObjectFactory.h"
#include "ControlSystem.h"

class Controller : public ControlSystem
{
public:
	Controller(Player& player, ObjectFactory& objectFactory);

	//void OnKeyDown(int keyCode);
	//void OnKeyUp(int keyCode);

	void Update(UpdateData& updateData) override;

private:
	Player& player;
	ObjectFactory& objectFactory;

	// Return true if holding both left and right key
	bool IsHoldingLeftAndRight();
	bool IsHoldingUpAndDown();

	bool PressSubweaponKeys(int keyCode);
	void UseSubweapon();
};
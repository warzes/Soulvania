#include "stdafx.h"
#include "Controller.h"
#include "Button.h"

Controller::Controller(Player& player, ObjectFactory& objectFactory) :
	player{ player },
	objectFactory{ objectFactory }
{
}

void Controller::Update(UpdateData& updateData)
{
	if (!enabled)
		return;

	if (player.IsAttacking())
		return;

	switch (player.GetMoveState())
	{
	case MoveState::IDLE:	

		if (IsHoldingLeftAndRight() || IsHoldingUpAndDown())
			break;
		else if (IsKeyDown(Button::WalkLeft))
			player.WalkLeft();
		else if (IsKeyDown(Button::WalkRight))
			player.WalkRight();
		else if (IsKeyDown(Button::GoUpstair) && player.CanGoUpstairs())
			player.WalkToStairs();
		else if (IsKeyDown(Button::GoDownstair) && player.CanGoDownstairs())
			player.WalkToStairs();
		else if (IsKeyDown(Button::Duck))
			player.Duck();

		else if (IsKeyPressed(Button::Jump))
			player.Jump();
		else if (PressSubweaponKeys())
			UseSubweapon();
		else if (IsKeyPressed(Button::Attack))
			player.Attack();

		break;

	case MoveState::IDLE_UPSTAIRS:
	case MoveState::IDLE_DOWNSTAIRS:

		if (PressSubweaponKeys())
			UseSubweapon();
		else if (IsKeyPressed(Button::Attack))
			player.Attack();

		if (IsHoldingUpAndDown())
			break;
		else if (IsKeyDown(Button::GoUpstair))
			player.GoUpstairs();
		else if (IsKeyDown(Button::GoDownstair))
			player.GoDownstairs();	

		break;

	case MoveState::WALKING:
		if (IsKeyUp(Button::WalkLeft) && player.GetFacing() == Facing::Left)
			player.Idle();
		if (IsKeyUp(Button::WalkRight) && player.GetFacing() == Facing::Right)
			player.Idle();

		if (IsHoldingLeftAndRight())
			player.Idle();
		else if (PressSubweaponKeys())
			UseSubweapon();
		else if (IsKeyPressed(Button::Attack))
			player.Attack();
		else if (IsKeyPressed(Button::Jump))
			player.Jump();
		else if (IsKeyPressed(Button::Duck))
			player.Duck();
		break;

	case MoveState::DUCKING:
		if (IsKeyUp(Button::Duck))
			player.Idle();
		if (IsHoldingUpAndDown())
			player.Idle();

		if (IsKeyDown(Button::WalkLeft))
			player.SetFacing(Facing::Left);
		else if (IsKeyDown(Button::WalkRight))
			player.SetFacing(Facing::Right);
		else if (PressSubweaponKeys())
			UseSubweapon();
		else if (IsKeyPressed(Button::Attack))
			player.Attack();

		break;

	case MoveState::JUMPING:
	case MoveState::HOVERING:
	case MoveState::FALLING:
	case MoveState::LANDING:
		if (PressSubweaponKeys())
			UseSubweapon();
		else if (IsKeyPressed(Button::Attack))
			player.Attack();
		break;
	}
}

bool Controller::IsHoldingLeftAndRight()
{
	return IsKeyDown(Button::WalkLeft) && IsKeyDown(Button::WalkRight);
}

bool Controller::IsHoldingUpAndDown()
{
	return IsKeyDown(Button::Duck) && IsKeyDown(Button::GoUpstair);
}

bool Controller::PressSubweaponKeys()
{
	if (IsKeyDown(Button::Attack))
	{
		if (IsKeyDown(Button::GoUpstair))
			return true;
	}
	return false;
}

void Controller::UseSubweapon()
{
	auto weaponItem = player.GetSubWeapon();

	if (weaponItem == ObjectId::Stopwatch)
	{
		player.Stoptime();
	}
	else
	{
		auto subWeapon = objectFactory.CreateSubWeapon(weaponItem);

		if (subWeapon != nullptr)
			player.Throw(std::move(subWeapon));
	}
}
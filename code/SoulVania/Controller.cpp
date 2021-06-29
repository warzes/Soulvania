#include "stdafx.h"
#include "Controller.h"
#include "Button.h"

Controller::Controller(Player& player, ObjectFactory& objectFactory) :
	player{ player },
	objectFactory{ objectFactory }
{
}

//void Controller::OnKeyDown(int keyCode)
//{
//	if (!enabled)
//		return;
//
//	if (player.IsAttacking())
//		return;
//
//	switch (player.GetMoveState())
//	{
//	case MoveState::IDLE:
//		if (keyCode == Button::Jump)
//			player.Jump();
//		else if (PressSubweaponKeys(keyCode))
//			UseSubweapon();
//		else if (keyCode == Button::Attack)
//			player.Attack();
//		break;
//
//	case MoveState::WALKING:
//		if (IsHoldingLeftAndRight())
//			player.Idle();
//		else if (PressSubweaponKeys(keyCode))
//			UseSubweapon();
//		else if (keyCode == Button::Attack)
//			player.Attack();
//		else if (keyCode == Button::Jump)
//			player.Jump();
//		else if (keyCode == Button::Duck)
//			player.Duck();
//		break;
//
//	case MoveState::IDLE_UPSTAIRS:
//	case MoveState::IDLE_DOWNSTAIRS:
//		if (PressSubweaponKeys(keyCode))
//			UseSubweapon();
//		else if (keyCode == Button::Attack)
//			player.Attack();
//		break;
//
//	case MoveState::JUMPING:
//	case MoveState::HOVERING:
//	case MoveState::FALLING:
//	case MoveState::LANDING:
//		if (PressSubweaponKeys(keyCode))
//			UseSubweapon();
//		else if (keyCode == Button::Attack)
//			player.Attack();
//		break;
//
//	case MoveState::DUCKING:
//		if (keyCode == Button::WalkLeft)
//			player.SetFacing(Facing::Left);
//		else if (keyCode == Button::WalkRight)
//			player.SetFacing(Facing::Right);
//		else if (PressSubweaponKeys(keyCode))
//			UseSubweapon();
//		else if (keyCode == Button::Attack)
//			player.Attack();
//		break;
//	}
//}
//
//void Controller::OnKeyUp(int keyCode)
//{
//	if (!enabled)
//		return;
//
//	if (player.IsAttacking())
//		return;
//}

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
		break;

	case MoveState::IDLE_UPSTAIRS:
	case MoveState::IDLE_DOWNSTAIRS:
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
		break;

	case MoveState::DUCKING:
		if (IsKeyUp(Button::Duck))
			player.Idle();
		if (IsHoldingUpAndDown())
			player.Idle();
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

bool Controller::PressSubweaponKeys(int keyCode)
{
	if (keyCode == Button::Attack)
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
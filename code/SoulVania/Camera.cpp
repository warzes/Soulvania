#include "stdafx.h"
#include "Camera.h"
#include "MathHelper.h"
#include <raylib/raylib.h>

namespace base
{

	Camera::Camera()
	{
		moveArea = Rect::Empty();

		viewport.x = 0;
		viewport.y = 0;
		viewport.width = GetScreenWidth();
		viewport.height = GetScreenHeight();

		thisCamera = this;
	}

	void Camera::SetMoveArea(int x, int y, int width, int height)
	{
		SetMoveArea(Rect(x, y, width, height));
	}

	void Camera::SetMoveArea(Rect moveArea)
	{
		this->moveArea = moveArea;
	}

	RectF Camera::GetBounds()
	{
		return viewport.Bounds();
	}

	void Camera::SetPosition(base::Vector2 position)
	{
		viewport.x = position.x;
		viewport.y = position.y;
	}

	void Camera::Move(base::Vector2 position)
	{
		viewport.x += position.x;
		viewport.y += position.y;

		ClampMove();
	}

	void Camera::LookAt(base::Vector2 position, Scrolling scrolling)
	{
		if (scrolling == Scrolling::Center || scrolling == Scrolling::Horizontally)
			viewport.x = position.x - viewport.width / 2;

		if (scrolling == Scrolling::Center || scrolling == Scrolling::Vertically)
			viewport.y = position.y - viewport.height / 2;

		ClampMove();
	}

	void Camera::Lock()
	{
		SetMoveArea((Rect)GetBounds());
	}

	base::Vector2 Camera::ScreenToWorld(base::Vector2 screenPosition)
	{
		return viewport.Unproject(screenPosition);
	}

	base::Vector2 Camera::WorldToScreen(base::Vector2 worldPosition)
	{
		return viewport.Project(worldPosition);
	}

	void Camera::ClampMove()
	{
		if (moveArea == Rect::Empty())
			return;

		viewport.x = MathHelper::Min(viewport.x, (float)moveArea.X() + (float)moveArea.Width() - viewport.width);
		viewport.y = MathHelper::Min(viewport.y, (float)moveArea.Y() + (float)moveArea.Height() - viewport.height);
		viewport.x = MathHelper::Max(viewport.x, (float)moveArea.X());
		viewport.y = MathHelper::Max(viewport.y, (float)moveArea.Y());
	}

}
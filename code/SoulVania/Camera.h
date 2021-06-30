#pragma once

#include "Rect.h"
#include "Vector2.h"
#include "Viewport.h"

namespace base
{

	enum class Scrolling
	{
		Horizontally,
		Vertically,
		Center,
	};

	class Camera
	{
	public:
		Camera();

		static inline Camera* thisCamera = nullptr;

		void SetMoveArea(int x, int y, int width, int height);
		void SetMoveArea(Rect moveArea);
		RectF GetBounds();
		Viewport& GetViewport() { return viewport; }

		void SetPosition(base::Vector2 position);
		void Move(base::Vector2 position);
		void LookAt(base::Vector2 position, Scrolling scrolling = Scrolling::Center);
		void Lock();

		base::Vector2 ScreenToWorld(base::Vector2 screenPosition);
		base::Vector2 WorldToScreen(base::Vector2 worldPosition);

	private:
		Rect moveArea;
		Viewport viewport;// = graphicsDevice.GetViewport();

		void ClampMove();
	};
}
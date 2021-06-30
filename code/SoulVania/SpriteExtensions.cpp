#include "stdafx.h"
#include "SpriteExtensions.h"
#include "Camera.h"

void SpriteExtensions::Draw(Sprite sprite, base::Vector2 position, bool useViewport)
{
	Draw(sprite, position, 0.0f, base::Vector2::One(), useViewport);
}

void SpriteExtensions::Draw(Sprite sprite, base::Transform transform, bool useViewport)
{
	Draw(sprite, transform.position, transform.rotation, transform.scale, useViewport);
}

void SpriteExtensions::Draw(Sprite sprite, base::Vector2 position, float rotation, base::Vector2 scale, bool useViewport)
{
	if (sprite.IsVisible())
	{
		auto& texture = sprite.GetTextureRegion().GetTexture();
		auto spriteFrame = sprite.GetTextureRegion().GetFrameRectangle();
		auto color = sprite.GetColor() * sprite.GetAlpha();
		auto effects = sprite.GetEffect();

		if (useViewport && base::Camera::thisCamera)
		{
			auto viewportRect = base::Camera::thisCamera->GetBounds(); // TODO: hack
			auto spriteRect = sprite.GetFrameRectangle(position);
			if (!viewportRect.TouchesOrIntersects(spriteRect)) // Dont draw if object is outside of viewport
				return;
		}

		Draw(texture, position, &spriteFrame, color, rotation, scale, effects, useViewport);
	}
}
#pragma once

#include "Sprite.h"
#include "RenderingSystem.h"

// Simple rendering system that draw the full texure
class SpriteRenderingSystem : public RenderingSystem
{
public:
	SpriteRenderingSystem(GameObject& parent, std::string spritePath);
	SpriteRenderingSystem(GameObject& parent, TextureRegion textureRegion);

	Sprite& GetSprite() override;
	GameObject& GetParent() override;

	void LoadContent(ContentManager& content) override;
	void Draw(SpriteExtensions& spriteBatch) override;

protected:
	GameObject& parent;
	std::unique_ptr<Sprite> sprite;
	std::string spritePath;
};
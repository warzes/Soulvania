#pragma once

#include "AnimatedSprite.h"
#include "RenderingSystem.h"

class AnimationRenderingSystem : public RenderingSystem
{
public:
	AnimationRenderingSystem(GameObject& parent, std::string spriteConfigPath);

	Sprite& GetSprite() override;
	GameObject& GetParent();

	void LoadContent(ContentManager& content) override;
	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

protected:
	GameObject& parent;
	std::unique_ptr<AnimatedSprite> sprite;
	std::string spriteConfigPath;
};
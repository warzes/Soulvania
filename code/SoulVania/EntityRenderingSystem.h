#pragma once

#include "AnimatedSprite.h"
#include "RenderingSystem.h"
#include "IEffect.h"

// Rendering system for interactive objects that spawns effect when being hit
	// and when about to die (candle, enemies)
class EntityRenderingSystem : public RenderingSystem
{
public:
	EntityRenderingSystem(
		GameObject& parent,
		std::string spriteConfigPath,
		std::unique_ptr<IEffect> deadEffect,
		std::unique_ptr<IEffect> hitEffect);

	Sprite& GetSprite() override;
	GameObject& GetParent() override;

	void LoadContent(ContentManager& content) override;
	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

protected:
	std::unique_ptr<AnimatedSprite> sprite;

private:
	GameObject& parent;
	std::string spriteConfigPath;
	std::unique_ptr<IEffect> deadEffect;
	std::unique_ptr<IEffect> hitEffect;

	void OnStateChanged() override;
	void OnTakingDamage() override;
};
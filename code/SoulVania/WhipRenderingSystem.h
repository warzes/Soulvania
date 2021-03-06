#pragma once

#include "AnimatedSprite.h"
#include "RenderingSystem.h"

class Whip;

class WhipRenderingSystem : public RenderingSystem
{
public:
	WhipRenderingSystem(Whip& parent, std::string spriteConfigPath);

	AnimatedSprite& GetSprite() override;
	GameObject& GetParent() override;

	virtual void Receive(int message) override;

	void LoadContent(ContentManager& content) override;
	void Update(GameTime gameTime) override;
	void Draw(SpriteExtensions& spriteBatch) override;

protected:
	Whip& parent;
	std::unique_ptr<AnimatedSprite> sprite;
	std::string spriteConfigPath;

	virtual void OnWhipUnleashed();
	virtual void OnWhipWithdrawn();

	void UpdatePositionRelativeToPlayer();
};
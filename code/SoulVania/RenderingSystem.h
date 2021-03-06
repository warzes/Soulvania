#pragma once

#include "Sprite.h"
#include "IRenderingSystem.h"

// Base rendering system shipped with a bounding box drawer
class RenderingSystem : public IRenderingSystem
{
public:
	RenderingSystem();

	virtual Sprite& GetSprite() override = 0;
	virtual GameObject& GetParent();

	virtual void Receive(int message) override;

	static void LoadContent(ContentManager& content);
	static void DrawBoundingBox(SpriteExtensions& spriteBatch, RectF boundingBox, base::Color color);

	virtual void Update(GameTime gameTime) override;
	virtual void Draw(SpriteExtensions& spriteBatch) override;

	bool DrawDebug();

protected:
	static std::shared_ptr<Texture> bboxTexture;

	virtual void OnMoveStateChanged();
	virtual void OnStateChanged();
	virtual void OnTakingDamage();

private:
	base::Color GetBoundingBoxColor();
};
#pragma once

#include "IReceiver.h"
#include "ContentManager.h"
#include "GameTime.h"

class GameObject;

class IRenderingSystem : public IReceiver
{
public:
	virtual Sprite& GetSprite() = 0;

	virtual void LoadContent(ContentManager& content) = 0;
	virtual void Update(GameTime gameTime) = 0;
	virtual void Draw(SpriteExtensions& spriteBatch) = 0;

	virtual ~IRenderingSystem() {}
};
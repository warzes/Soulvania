#pragma once

#include "Vector2.h"
#include "ContentManager.h"
#include "AnimatedSprite.h"

enum class TestDirection
{
	Left,
	Right,
};

class TestGameObject
{
public:
	TestGameObject();

	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);

	virtual void LoadContent(ContentManager& content) = 0;

	virtual void Update(float deltaTime);
	void UpdateDistance(float deltaTime);

	virtual void Draw(SpriteBatch& spriteBatch);
	virtual ~TestGameObject();

protected:
	base::Vector2 position;
	base::Vector2 velocity;
	TestDirection direction;

	std::unique_ptr<AnimatedSprite> sprite;
};
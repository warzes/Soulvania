#pragma once

#include "TestGameObject.h"

enum class State
{
	WALKING_LEFT,
	WALKING_RIGHT,
	IDLE,
	JUMPING,
};

class Mario : public TestGameObject
{
public:
	State GetState();

	void LoadContent(ContentManager& content) override;
	void Update(float deltaTime) override;
	void Draw(SpriteBatch& spriteBatch) override;

	void Jump();
	void Jumping();
	void Idle();
	void WalkLeft();
	void WalkRight();

private:
	State state;

	void UpdateState();
	void ResolveCollision(float deltaTime);
};
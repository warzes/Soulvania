#pragma once

#include "TestGameObject.h"
#include "TestController.h"

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
	Mario();
	State GetState();
	TestController* GetController();

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
	TestController controller;

	void UpdateState();
	void ResolveCollision(float deltaTime);
};
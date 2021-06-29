#include "stdafx.h"
#include "TestGameObject.h"

TestGameObject::TestGameObject()
{
	position = base::Vector2::Zero();
	velocity = base::Vector2::Zero();

	direction = TestDirection::Right;
}

void TestGameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void TestGameObject::SetSpeed(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void TestGameObject::LoadContent(ContentManager& content)
{
}

void TestGameObject::Update(float deltaTime)
{
}

void TestGameObject::UpdateDistance(float deltaTime)
{
	position.x = position.x + velocity.x * deltaTime;
	position.y = position.y + velocity.y * deltaTime;
}

void TestGameObject::Draw(SpriteBatch& spriteBatch)
{
}

TestGameObject::~TestGameObject()
{
}
#include "stdafx.h"
#include "Mario.h"
#include "TestSettings.h"
#include "TestAudioManager.h"

State Mario::GetState()
{
	return state;
}


void Mario::LoadContent(ContentManager& content)
{
	auto animationFactory = content.Load<AnimationFactory>("MarioAnimation.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
	SetPosition(0.0f, 100.0f);
	Idle();
}

void Mario::Update(float deltaTime)
{
	// Input
	switch (GetState())
	{
	case State::IDLE:
		if (IsKeyPressed(KEY_SPACE))
			Jump();
		if (IsKeyPressed(KEY_RIGHT))
			WalkRight();
		else if (IsKeyPressed(KEY_LEFT))
			WalkLeft();
		break;
	}

	if (IsKeyDown(KEY_SPACE))
	{
		switch (GetState())
		{
		case State::IDLE:
		case State::WALKING_LEFT:
		case State::WALKING_RIGHT:
			Jump();
			break;
		}
	}
	
	if (IsKeyUp(KEY_LEFT))
	{
		switch (GetState())
		{
		case State::WALKING_LEFT:
			Idle();
			break;
		}
	}

	if (IsKeyUp(KEY_RIGHT))
	{
		switch (GetState())
		{
		case State::WALKING_RIGHT:
			Idle();
			break;
		}
	}

	UpdateState();
	ResolveCollision(deltaTime);
}

void Mario::UpdateState()
{
	switch (state)
	{
	case State::JUMPING:
		Jumping();
		break;
	}
}

void Mario::ResolveCollision(float deltaTime)
{
	TestGameObject::UpdateDistance(deltaTime);

	// simple fall down
	velocity.y += MARIO_GRAVITY;
	if (position.y > 100)
	{
		velocity.y = 0;
		position.y = 100.0f;
	}

	// simple screen edge collision!!!
	if (velocity.x > 0 && position.x > 305)
	{
		position.x = 305;
	}
	if (velocity.x < 0 && position.x < 0)
	{
		position.x = 0;
	}
}

void Mario::Jump()
{
	state = State::JUMPING;
}

void Mario::Jumping()
{
	if (position.y == 100)
	{
		TestAudioManager::Play("Jump");
		velocity.y = -MARIO_JUMP_SPEED_Y;
	}
	else
		state = State::IDLE;
}

void Mario::Idle()
{
	state = State::IDLE;
	velocity.x = 0;
	sprite->Play(MARIO_IDLE);
}

void Mario::WalkLeft()
{
	state = State::WALKING_LEFT;
	velocity.x = -MARIO_WALKING_SPEED;
	direction = Direction::Left;
	sprite->Play(MARIO_WALK);
}

void Mario::WalkRight()
{
	state = State::WALKING_RIGHT;
	velocity.x = MARIO_WALKING_SPEED;
	direction = Direction::Right;
	sprite->Play(MARIO_WALK);
}

void Mario::Draw(SpriteBatch& spriteBatch)
{
	auto effect = direction == Direction::Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	auto& texture = sprite->GetTextureRegion().GetTexture();
	auto srcRectangle = sprite->GetTextureRegion().GetFrameRectangle();

	printf("x=%d y=%d w=%d h=%d\n", srcRectangle.left, srcRectangle.top, srcRectangle.right, srcRectangle.bottom);

	sprite->Update();
	spriteBatch.Draw(texture, position, &srcRectangle, base::Color::White(), 0.0f, base::Vector2::One(), effect);
}
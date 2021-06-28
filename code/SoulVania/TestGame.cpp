#include "stdafx.h"
#include "TestGame.h"
#include <raylib/raylib.h>

// textures_sprite_button

TestGame::TestGame()
{
	content->SetRootDirectory("MarioSample/Content");
}

void TestGame::Initialize()
{
	Game::Initialize();
}

void TestGame::LoadContent()
{
}

void TestGame::Update(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
}

void TestGame::Draw(GameTime gameTime)
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Hello World!", 190, 200, 20, RED);

	EndDrawing();
}
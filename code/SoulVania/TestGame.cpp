#include "stdafx.h"
#include "TestGame.h"
#include "Color.h"
#include "TestAudioManager.h"
#include <raylib/raylib.h>

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
	spriteBatch = std::make_unique<SpriteBatch>();

	TestAudioManager::LoadContent(*content, { "Jump", "Overworld" });
	gameFont = content->Load<Font>("Roboto.spritefont");

	mario = std::make_shared<Mario>();
	mario->LoadContent(*content);

	TestAudioManager::PlaySong("Overworld");
}

void TestGame::Update(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	mario->Update(deltaTime);
}

void TestGame::Draw(GameTime gameTime)
{
	BeginDrawing();

	auto c = base::Color::LavenderBlue();
	ClearBackground({(unsigned char)c.R(), (unsigned char)c.G(), (unsigned char)c.B(), 255});

	mario->Draw(*spriteBatch);
	spriteBatch->DrawString(*gameFont, "Press arrow keys to move", base::Vector2{ 30, 30 }, base::Color{ 255, 0, 255 });

	EndDrawing();
}
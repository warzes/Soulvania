#include "stdafx.h"
#include "Game.h"
#include <raylib/raylib.h>

//const int screenWidth = 320;
//const int screenHeight = 240;
const int screenWidth = 512;
const int screenHeight = 448;

Game::Game()
{
	framePerSecond = 1000;
	tickPerFrame = 1000 / framePerSecond;

	service = std::make_shared<ServiceProvider>();
	content = std::make_unique<ContentManager>(service);
}

void Game::Run()
{
	Initialize();

	gameTimer.Start();
	while (!WindowShouldClose())
	{
		Tick();
		auto deltaTime = (int)gameTime.ElapsedGameTime.Milliseconds();

		Update(gameTime);
		Render(gameTime);
	}
	CloseAudioDevice();     // Close audio device
	CloseWindow();
}

void Game::Initialize()
{
	InitWindow(screenWidth, screenHeight, "Soulvania");
	SetTargetFPS(60);
	SetExitKey(0);

	//InitAudioDevice();      // Initialize audio device

	LoadContent();
}

void Game::LoadContent()
{
}

void Game::Update(GameTime gameTime)
{
}

void Game::Draw(GameTime gameTime)
{
}

void Game::Render(GameTime gameTime)
{
	Draw(gameTime);
}

void Game::Tick()
{
	auto currentTick = gameTimer.ElapsedMilliseconds();
	auto accumulatedTime = TimeSpan::FromMilliseconds(currentTick - gameTime.GetPreviousTicks());

	gameTime.SetPreviousTicks(currentTick);
	gameTime.ElapsedGameTime = accumulatedTime;
	gameTime.TotalGameTime += accumulatedTime;
}

ContentManager& Game::GetContent()
{
	return *content;
}
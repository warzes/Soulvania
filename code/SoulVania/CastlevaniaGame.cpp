#include "stdafx.h"
#include "CastlevaniaGame.h"
#include "AudioManager.h"

CastlevaniaGame::CastlevaniaGame()
{
	content->SetRootDirectory("Castlevania/Content");
}

void CastlevaniaGame::Initialize()
{
	Game::Initialize();
	sceneManager = std::make_unique<SceneManager>(*this);
	sceneManager->SetNextScene(Scene::MENU);
}

void CastlevaniaGame::LoadContent()
{
	AudioManager::LoadContent(*content);
}

void CastlevaniaGame::Update(GameTime gameTime)
{
	sceneManager->Update(gameTime);
}

void CastlevaniaGame::Draw(GameTime gameTime)
{
	BeginDrawing();

	auto c = base::Color::LavenderBlue();
	ClearBackground({ (unsigned char)c.R(), (unsigned char)c.G(), (unsigned char)c.B(), 255 });

	sceneManager->Draw(gameTime);

	EndDrawing();
}
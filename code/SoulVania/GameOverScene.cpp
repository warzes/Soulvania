#include "stdafx.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "AudioManager.h"
#include <raylib/raylib.h>

constexpr auto GAME_OVER_TEXT = "GAME OVER";
constexpr auto CONTINUE_TEXT = "CONTINUE";
constexpr auto END_TEXT = "END";

GameOverScene::GameOverScene(SceneManager& sceneManager) : AbstractScene{ sceneManager }
{
	currentOption = CONTINUE_TEXT;
}

void GameOverScene::LoadContent()
{
	auto& content = sceneManager.GetContent();

	font = content.Load<Font>("Fonts/MainFont.font.xml");
	heartTexture = content.Load<Texture>("Hud/Heart.png");

	auto gameOverTextSize = MeasureTextEx(*font, GAME_OVER_TEXT, font->baseSize, 1); // TODO:

	gameOverTextPosition.x = (GetScreenWidth() - gameOverTextSize.x) / 2;
	gameOverTextPosition.y = (GetScreenHeight() - gameOverTextSize.y) / 2;

	continueTextPosition.x = gameOverTextPosition.x + 12;
	continueTextPosition.y = gameOverTextPosition.y + 80;

	endTextPosition.x = gameOverTextPosition.x + 12;
	endTextPosition.y = gameOverTextPosition.y + 130;

	AudioManager::Play(M_GAME_OVER);
}

void GameOverScene::Update(GameTime gameTime)
{
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP))
	{
		if (currentOption == CONTINUE_TEXT)
			currentOption = END_TEXT;
		else
			currentOption = CONTINUE_TEXT;
	}

	if (IsKeyDown(KEY_ENTER))
	{
		if (currentOption == CONTINUE_TEXT)
		{
			auto& scene = sceneManager.SetNextScene(Scene::GAMEPLAY);
			dynamic_cast<GameplayScene&>(scene).NextStage(Map::COURTYARD);
		}
		else
			sceneManager.SetNextScene(Scene::MENU);
	}
}

void GameOverScene::Draw(GameTime gameTime)
{
	auto& spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(0/*D3DXSPRITE_ALPHABLEND*/);

	spriteBatch.Draw(*heartTexture, GetHeartPosition(), base::Color::White(), false);
	spriteBatch.DrawString(*font, GAME_OVER_TEXT, gameOverTextPosition, base::Color::White(), false);
	spriteBatch.DrawString(*font, CONTINUE_TEXT, continueTextPosition, base::Color::White(), false);
	spriteBatch.DrawString(*font, END_TEXT, endTextPosition, base::Color::White(), false);

	spriteBatch.End();
}

base::Vector2 GameOverScene::GetHeartPosition()
{
	if (currentOption == CONTINUE_TEXT)
		return base::Vector2{ continueTextPosition.x - 30, continueTextPosition.y };
	else
		return base::Vector2{ endTextPosition.x - 30, endTextPosition.y };
}
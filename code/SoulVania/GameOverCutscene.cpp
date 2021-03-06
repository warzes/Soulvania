#include "stdafx.h"
#include "GameOverCutscene.h"
#include "Stage.h"
#include "StageEvent.h"
#include "SceneManager.h"
#include "GameplayScene.h"
#include "AudioManager.h"

enum class GameOverCutscene::State
{
	BEFORE_PLAYING_CUTSCENE,
	PLAYING_CUTSCENE,
};

constexpr auto TRANSITION_WAITING_TIME = 1200; // in milliseconds
constexpr auto RESET_TRANSITION_TIME = 400; // in milliseconds

GameOverCutscene::GameOverCutscene(Stage& stage, ContentManager& content, GameplayScene& gameplayScene) :
	Cutscene{ stage },
	gameplayScene{ gameplayScene }
{
	auto cutsceneTexture = content.Load<Texture>("Backgrounds/Cutscene_Background.png");
	cutsceneBackground = std::make_unique<Sprite>(cutsceneTexture);
	currentState = State::BEFORE_PLAYING_CUTSCENE;

	transitionTimer.Start();
}

void GameOverCutscene::Update(UpdateData& updateData)
{
	switch (currentState)
	{
	case State::BEFORE_PLAYING_CUTSCENE:
		if (transitionTimer.ElapsedMilliseconds() >= TRANSITION_WAITING_TIME)
		{
			transitionTimer.Restart();
			currentState = State::PLAYING_CUTSCENE;
		}
		break;

	case State::PLAYING_CUTSCENE:
		if (transitionTimer.ElapsedMilliseconds() >= RESET_TRANSITION_TIME)
		{
			stage.GetCamera()->SetPosition(base::Vector2::Zero());
			gameplayScene.GetSceneManager().SetNextScene(Scene::GAMEOVER);
		}
		break;
	}
}

void GameOverCutscene::Draw(SpriteExtensions& spriteBatch)
{
	switch (currentState)
	{
	case State::BEFORE_PLAYING_CUTSCENE:
		Cutscene::Draw(spriteBatch);
		break;

	case State::PLAYING_CUTSCENE:
		spriteBatch.Draw(*cutsceneBackground, base::Vector2::Zero(), false);
		break;
	}
}
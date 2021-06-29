#pragma once

#include "ContentManager.h"
#include "Stopwatch.h"
#include "Cutscene.h"

class GameplayScene;

class GameOverCutscene : public Cutscene
{
public:
	GameOverCutscene(Stage& stage, ContentManager& content, GameplayScene& gameplayScene);

	void Update(UpdateData& updateData) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	enum class State;

	GameplayScene& gameplayScene;
	std::unique_ptr<Sprite> cutsceneBackground;
	Stopwatch transitionTimer;
	State currentState;
};
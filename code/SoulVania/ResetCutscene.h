#pragma once

#include "ContentManager.h"
#include "Stopwatch.h"
#include "Cutscene.h"

class ResetCutscene : public Cutscene
{
public:
	ResetCutscene(Stage& stage, ContentManager& content);

	void Update(UpdateData& updateData) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	enum class State;

	std::unique_ptr<Sprite> cutsceneBackground;
	Stopwatch transitionTimer;
	State currentState;
};
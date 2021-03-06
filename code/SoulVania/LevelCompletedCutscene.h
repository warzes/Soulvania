#pragma once

#include "Cutscene.h"
#include "GameplayData.h"
#include "ObjectFactory.h"

class LevelCompletedCutscene : public Cutscene
{
public:
	LevelCompletedCutscene(
		Stage& stage,
		CollisionGrid& grid,
		ObjectFactory& objectFactory,
		Player& player,
		GameplayData& gameplayData);

	void Update(UpdateData& updateData) override;

private:
	enum class State;

	Player& player;
	GameplayData& gameplayData;
	State currentState;
	GameObject* crystalBall;
	Stopwatch soundEffectTimer;
	Stopwatch transitionTimer;
	Stopwatch scoreUpdateTimer;
};
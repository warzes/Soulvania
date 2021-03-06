#pragma once

#include "Cutscene.h"

class Stage;

class IntroCutscene : public Cutscene
{
public:
	IntroCutscene(Stage& stage, CollisionGrid& grid, Player& player);

	void Update(UpdateData& updateData) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	enum class State;

	Player& player;
	float playerOriginalSpeed;
	Trigger* nextMapTrigger;
	Vector2 gatePosition;
	State currentState;
	Stopwatch transitionTimer;
	bool isFinished;
};
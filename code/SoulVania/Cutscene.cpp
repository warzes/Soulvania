#include "stdafx.h"
#include "Cutscene.h"
#include "Stage.h"

Cutscene::Cutscene(Stage& stage) : stage{ stage }
{
	isComplete = false;
}

bool Cutscene::IsComplete()
{
	return isComplete;
}

void Cutscene::Draw(SpriteExtensions& spriteBatch)
{
	stage.DrawGameplay(spriteBatch);
}
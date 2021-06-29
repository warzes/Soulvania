#pragma once

#include "ContentManager.h"
#include "Stopwatch.h"
#include "Cutscene.h"

class NextMapCutscene : public Cutscene
{
public:
	NextMapCutscene(Stage& stage, ContentManager& content);

	void Update(UpdateData& updateData) override;
	void Draw(SpriteExtensions& spriteBatch) override;

private:
	std::unique_ptr<Sprite> cutsceneBackground;
	Stopwatch transitionTimer;
};
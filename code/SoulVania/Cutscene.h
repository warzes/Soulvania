#pragma once

#include "IDrawable.h"
#include "StageObject.h"
#include "UpdateData.h"
#include "ObjectFactory.h"
#include "CollisionGrid.h"

class Stage;

class Cutscene : public IDrawable
{
public:
	Cutscene(Stage& stage);

	bool IsComplete();

	virtual void Update(UpdateData& updateData) = 0;
	virtual void Draw(SpriteExtensions& spriteBatch) override;

protected:
	Stage& stage;
	bool isComplete;
};
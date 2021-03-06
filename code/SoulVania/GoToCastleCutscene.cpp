#include "stdafx.h"
#include "GoToCastleCutscene.h"
#include "Stage.h"
#include "AudioManager.h"

enum class GoToCastleCutscene::State
{
	WALKING_TO_CASTLE_GATE,
	WALKING_TO_NEXT_MAP,
};

GoToCastleCutscene::GoToCastleCutscene(Stage& stage, ObjectCollection& objectCollection, CollisionGrid& grid, Player& player) :
	Cutscene{ stage }
{
	this->player = &player;

	grid.GetCellsFromBoundingBox(stage.GetCamera()->GetBounds(), [&](CollisionCell& cell, int col, int row)
		{
			auto& objects = cell.GetObjects();

			for (auto& object : objects.staticObjects)
			{
				if (object->GetId() != ObjectId::Trigger)
					continue;

				auto trigger = dynamic_cast<Trigger*>(object.get());

				if (trigger->GetTriggerType() == TriggerType::MONEY_BAG_EASTER_EGG)
					trigger->GetBody().Enabled(false);

				if (trigger->GetTriggerType() == TriggerType::CASTLE_ENTRANCE)
					entranceTrigger = trigger;

				if (trigger->GetTriggerType() == TriggerType::NEXT_MAP)
					nextMapTrigger = trigger;
			}
		});

	for (auto& object : objectCollection.foregroundObjects)
	{
		if (object->GetId() == ObjectId::Castle)
		{
			castle = object.get();
			break;
		}
	}

	// Remove objects before cutscene even started is not necessary
	// But I will leave it here to mimic the original game behaviour
	grid.GetAllCells([&](CollisionCell& cell)
		{
			cell.GetEntites().clear();
		});

	SetupCutscene();
}

void GoToCastleCutscene::SetupCutscene()
{
	playerOriginalSpeed = player->GetSpeed();

	player->SetSpeed(playerOriginalSpeed / 3);
	player->EnableControl(false);

	if (player->GetBoundingBox().right <= entranceTrigger->GetBoundingBox().right)
		player->WalkRight();
	else
		player->WalkLeft();

	nextMapTrigger->GetBody().Enabled(true);

	currentState = State::WALKING_TO_CASTLE_GATE;
	AudioManager::Play(SE_GOING_TO_CASTLE);
}

void GoToCastleCutscene::Update(UpdateData& updateData)
{
	stage.UpdateGameObjects(updateData);

	switch (currentState)
	{
	case State::WALKING_TO_CASTLE_GATE:
		if (player->GetBoundingBox().right <= entranceTrigger->GetBoundingBox().right)
		{
			if (player->GetFacing() == Facing::Left)
				player->WalkRight();

			castle->SetVisibility(true);
			currentState = State::WALKING_TO_NEXT_MAP;
		}
		break;

	case State::WALKING_TO_NEXT_MAP:
		if (player->GetNearbyObjects().nextMap != nullptr)
		{
			player->SetSpeed(playerOriginalSpeed);
			isComplete = true;
		}
		break;
	}
}
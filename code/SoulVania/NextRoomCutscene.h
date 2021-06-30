#pragma once

#include "Camera.h"
#include "Cutscene.h"
#include "Player.h"

class NextRoomCutscene : public Cutscene
{
public:
	NextRoomCutscene(
		Stage& stage,
		StageObject& stageObject,
		CollisionGrid& grid,
		ObjectFactory& objectFactory,
		Player& player);

	void Update(UpdateData& updateData) override;

private:
	enum class State;

	Player& player;
	CollisionGrid& grid;
	ObjectFactory& objectFactory;
	base::Camera& camera;
	Door& door;
	Direction doorHitDirection;

	State currentState;
	float viewportDestination_x;
	float playerDestination_x;
	float openDoorPosition_x;

	void SetupCutscene();
	void OnComplete();
};
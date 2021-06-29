#pragma once

#include "ControlSystem.h"
#include "ObjectFactory.h"
#include "GiantBat.h"

class GiantBatControlSystem : public ControlSystem
{
public:
	GiantBatControlSystem(GiantBat& parent, ObjectFactory& objectFactory);

	void Receive(int message) override;
	void Update(UpdateData& updateData) override;

private:
	GiantBat& parent;
	ObjectFactory& objectFactory;

	int hoveringTime;
	Stopwatch hoveringTimer;
	float minSpeed;
	float maxSpeed;
	float heightToStopDiving;
	base::Vector2 playerPosition;

	void OnMoveStateChanged();
	void OnActiveChanged();

	bool IsDistanceOutsideOfViewport(base::Vector2 distance);
	bool IsBelowPlayer();
	float GetSpeedRelativeToPlayerDistance();

	void MoveRandomly();
	void ClampMoveInArea();
	base::Vector2 RandomDirection();
};
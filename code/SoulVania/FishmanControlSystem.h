#pragma once

#include "Stopwatch.h"
#include "ControlSystem.h"
#include "ObjectFactory.h"
#include "Fishman.h"

class FishmanControlSystem : public ControlSystem
{
public:
	FishmanControlSystem(Fishman& parent, ObjectFactory& objectFactory);

	void Receive(int message) override;
	void Update(UpdateData& updateData) override;

private:
	Fishman& parent;
	FishmanState lastState;
	int shootingInterval; // Start shooting after an interval
	Stopwatch shootingIntervalTimer;
	ObjectFactory& objectFactory;

	void ResetShootingTimer();
};
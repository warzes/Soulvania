#pragma once

#include "Stopwatch.h"
#include "GameObject.h"

class Powerup : public GameObject
{
public:
	Powerup(ObjectId type, int lifeSpan = 0);

	void Spawn();
	void Update(UpdateData& updateData) override;

private:
	Stopwatch lifespanTimer;
	int lifeSpan;
};
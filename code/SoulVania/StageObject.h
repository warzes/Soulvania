#pragma once

#include "GameObject.h"
#include "Checkpoint.h"

struct StageObject
{
	std::vector<std::unique_ptr<GameObject>> stageAreas;
	std::map<std::string, Checkpoint> locations;
};
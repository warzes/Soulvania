#pragma once

#include "Door.h"
#include "AnimationRenderingSystem.h"

class DoorRenderingSystem : public AnimationRenderingSystem
{
public:
	DoorRenderingSystem(Door& parent, std::string animationPath);

private:
	Door& parent;
	void OnMoveStateChanged() override;
};
#pragma once

#include "GameObject.h"

class WaterArea : public GameObject
{
public:
	WaterArea();

	void Splash(base::Vector2 position);

private:
	base::Vector2 splashPosition;

	friend class WaterAreaRenderingSystem;
};
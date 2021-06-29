#pragma once

#include "IDrawable.h"
#include "IUpdateable.h"
#include "Vector2.h"

class IEffect : public IUpdateable, public IDrawable
{
public:
	virtual void Show(base::Vector2 position) = 0;
	virtual bool IsFinished() = 0;
};
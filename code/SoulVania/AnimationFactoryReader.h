#pragma once

#include "AbstractReader.h"
#include "AnimationFactory.h"

class AnimationFactoryReader : public AbstractReader<AnimationFactory>
{
public:
	std::shared_ptr<AnimationFactory> Read(std::string filePath, ContentManager& contentManager) override;
};
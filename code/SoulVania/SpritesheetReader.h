#pragma once

#include "AbstractReader.h"
#include "TextureRegion.h"

using Spritesheet = std::unordered_map<std::string, TextureRegion>;

class SpritesheetReader : public AbstractReader<Spritesheet>
{
public:
	std::shared_ptr<Spritesheet> Read(std::string filePath, ContentManager& contentManager) override;
};
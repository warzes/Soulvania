#pragma once

#include "AbstractReader.h"
#include <raylib/raylib.h>

class SoundReader : public AbstractReader<Sound>
{
public:
	std::shared_ptr<Sound> Read(std::string filePath, ContentManager& contentManager) override;
};
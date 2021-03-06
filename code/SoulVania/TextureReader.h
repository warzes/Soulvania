#pragma once

#include "AbstractReader.h"
#include <raylib/raylib.h>

class TextureReader : public AbstractReader<Texture>
{
public:
	std::shared_ptr<Texture> Read(std::string filePath, ContentManager& contentManager) override;
};
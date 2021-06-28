#pragma once

#include "AbstractReader.h"
#include <raylib/raylib.h>

enum class FontStyle
{
	Bold,
	Italic,
	Regular,
};

struct FontDescription
{
	std::string fontName;
	float size;
	FontStyle style;
};

class SpriteFontReader : public AbstractReader<Font>
{
public:
	std::shared_ptr<Font> Read(std::string filePath, ContentManager& contentManager) override;

private:
	FontDescription ReadFontConfig(std::string configFile);
};
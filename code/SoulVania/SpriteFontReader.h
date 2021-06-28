#pragma once

#include "AbstractReader.h"
#include "MyFont.h"

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

class SpriteFontReader : public AbstractReader<MyFont>
{
public:
	std::shared_ptr<MyFont> Read(std::string filePath, ContentManager& contentManager) override;

private:
	FontDescription ReadFontConfig(std::string configFile);
};
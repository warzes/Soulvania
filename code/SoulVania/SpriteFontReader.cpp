#include "stdafx.h"
#include "SpriteFontReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "WinHelper.h"
#include "FileLogger.h"
#include "pugixml/pugixml.hpp"

std::shared_ptr<Font> SpriteFontReader::Read(std::string configFile, ContentManager& contentManager)
{
	auto options = ReadFontConfig(configFile);
	auto filePathStr = (Path{ configFile }.parent_path() / options.fontName).string();

	if (!std::filesystem::exists(filePathStr))
		throw LoadContentException("Font file not found: " + configFile);

	auto filePath = WinHelper::s2ws(filePathStr);

	//Font fontTtf = LoadFontEx("resources/pixantiqua.ttf", options.32, 0, 250);
	return nullptr;
}

FontDescription SpriteFontReader::ReadFontConfig(std::string configFile)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(configFile.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error("{}() failed: {}. Path: {}", __FUNCTION__, result.description(), configFile);
		throw LoadContentException(result.description());
	}

	auto fontNode = xmlDocument.child("GameContent").child("Font");
	auto options = FontDescription{};
	static auto fontStyles = std::map<std::string, FontStyle>
	{
		{ "Regular", FontStyle::Regular },
		{ "Bold", FontStyle::Bold },
		{ "Italic", FontStyle::Italic },
	};

	options.fontName = fontNode.child("FontName").text().as_string();
	options.size = fontNode.child("Size").text().as_float();
	options.style = fontStyles.at(fontNode.child("Style").text().as_string());

	return options;
}
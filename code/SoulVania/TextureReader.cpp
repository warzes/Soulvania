#include "stdafx.h"
#include "TextureReader.h"

std::shared_ptr<Texture> TextureReader::Read(std::string filePathStr, ContentManager& contentManager)
{
	Texture2D tex = LoadTexture(filePathStr.c_str());
	return std::make_shared<Texture2D>(tex);
}
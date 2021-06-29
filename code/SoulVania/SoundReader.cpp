#include "stdafx.h"
#include "SoundReader.h"

std::shared_ptr<Sound> SoundReader::Read(std::string filePathStr, ContentManager& contentManager)
{
	Sound snd = LoadSound(filePathStr.c_str());
	return std::make_shared<Sound>(snd);
}
#pragma once

#include "AnimationFactoryReader.h"
#include "DictionaryReader.h"
#include "SoundReader.h"
#include "SpriteFontReader.h"
#include "SpritesheetReader.h"
#include "TextureReader.h"
#include "TiledMapReader.h"

// TODO: поудал€ть вс€кие фонты, саунды и спрайты отсюда

class ContentManager;

class ContentReader
{
public:
	ContentReader(ContentManager& contentManager);

	template<typename T>
	std::shared_ptr<T> ReadAsset(std::string path);

private:
	ContentManager& contentManager;

	AnimationFactoryReader animationFactoryReader;
	DictionaryReader dictionaryReader;
	SoundReader soundReader;
	SpriteFontReader spriteFontReader;
	SpritesheetReader spritesheetReader;
	TextureReader textureReader;
	TiledMapReader tiledMapReader;
};
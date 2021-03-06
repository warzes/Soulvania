#pragma once

#include "AbstractReader.h"
#include "TiledMap.h"
#include <pugixml/pugixml.hpp>

class TiledMapReader : public AbstractReader<TiledMap>
{
public:
	std::shared_ptr<TiledMap> Read(std::string filePath, ContentManager& contentManager) override;

private:
	std::unique_ptr<TileSet> ReadImageLayer(
		std::shared_ptr<Texture> tileSetTexture,
		int tileWidth,
		int tileHeight,
		int width,
		int height);

	std::unique_ptr<TileSet> ReadTileLayer(
		int tileLayerId,
		std::shared_ptr<Texture> tileSetTexture,
		std::vector<std::string> tileSetData,
		int tileWidth,
		int tileHeight,
		int width);

	TiledMapObjectGroups ReadTiledMapObjects(pugi::xml_node mapNode);
};
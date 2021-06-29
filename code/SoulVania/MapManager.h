#pragma once

#include "TiledMap.h"
#include "MapSettings.h"
#include "ObjectFactory.h"
#include "ObjectCollection.h"
#include "StageObject.h"

using ObjectProperties = std::unordered_map<std::string, std::string>;
using ObjectsProperties = std::vector<ObjectProperties>;

enum class MapObjectType
{
	Tile,
	Rectangle,
};

class MapManager
{
public:
	MapManager(ContentManager& content, ObjectFactory& objectFactory);

	void SetWorldPosition(base::Vector2 position);
	std::shared_ptr<TiledMap> GetTiledMap(Map name);
	std::unique_ptr<StageObject> GetStageObjects(Map name);
	ObjectCollection GetMapObjects(Map name);
	ObjectCollection GetMapObjectsInArea(Map name, RectF area);

	void GetLocations(std::map<std::string, Checkpoint>& objects, TiledMapObjectGroups& objectGroups);
	void GetStageAreas(std::vector<std::unique_ptr<GameObject>>& objects, TiledMapObjectGroups& objectGroups);
	void GetTriggers(std::vector<std::unique_ptr<GameObject>>& objects, TiledMapObjectGroups& objectGroups, RectF area);
	void GetEntities(std::vector<std::unique_ptr<GameObject>>& objects, TiledMapObjectGroups& objectGroups, RectF area);
	void GetBounds(std::vector<std::unique_ptr<GameObject>>& objects, TiledMapObjectGroups& objectGroups, RectF area);
	void GetAreas(std::vector<std::unique_ptr<GameObject>>& objects, TiledMapObjectGroups& objectGroups, RectF area);
	void GetForegrounds(std::vector<std::unique_ptr<GameObject>>& objects, TiledMapObjectGroups& objectGroups, RectF area);

private:
	std::map<Map, std::string> maps;

	base::Vector2 worldPosition; // absolute position of map and map objects to the world
	ContentManager& content;
	ObjectFactory& objectFactory;

	std::unique_ptr<GameObject> ConstructObject(ObjectProperties properties);
	RectF GetMapObjectBoundingBox(ObjectProperties properties, MapObjectType type);
};
#pragma once

#include "GameTime.h"
#include "SpriteExtensions.h"
#include "TiledMap.h"
#include "Camera.h"
#include "Cutscene.h"
#include "StageObject.h"
#include "ObjectFactory.h"
#include "ObjectCollection.h"
#include "IObserver.h"
#include "MapSettings.h"
#include "DevTool.h"
#include "Hud.h"

class GameplayScene;

enum class GameState
{
	PLAYING,
	INTRO_CUTSCENE,
	BOSS_FIGHT_CUTSCENE,
	NEXT_MAP_CUTSCENE,
	NEXT_ROOM_CUTSCENE,
	LEVEL_COMPLETED_CUTSCENE,
	GAMEOVER_CUTSCENE,
	RESET_STAGE_CUTSCENE,
	CROSS_CUTSCENE,
	STOPWATCH_CUTSCENE,
	HIDDEN_MONEYBAG_CUTSCENE,
	GO_TO_CASTLE_CUTSCENE,
};

class Stage : public IObserver
{
public:
	Stage(GameplayScene& gameplayScene, Map map, std::string spawnPoint);

	void OnNotify(Subject& subject, int event);

	base::Camera* GetCamera();
	Hud* GetHud();
	Rect GetActiveArea();

	void LoadObjectsWithin(Rect area);
	void ClearObjectsWithin(Rect area, std::set<GameObject*> exceptionList = std::set<GameObject*>{});

	void UpdateGameObjects(UpdateData& updateData);
	void UpdateGameplay(UpdateData& updateData);
	void DrawGameplay(SpriteExtensions& spriteBatch);

	void Initialize();
	void Update(GameTime gameTime);
	void Draw(SpriteExtensions& spriteBatch);

	~Stage();

private:
	struct StageEvent;

	GameplayScene& gameplayScene;
	ObjectFactory& objectFactory;
	GameState currentState;
	Map currentMap;
	Rect activeArea;
	std::string spawnPoint;
	std::unique_ptr<Cutscene> currentCutscene;
	std::unique_ptr<StageEvent> newEvent;

	std::shared_ptr<TiledMap> map;
	std::unique_ptr<base::Camera> camera;
	std::shared_ptr<Hud> hud;
	std::shared_ptr<GameplayData> data;
	std::unique_ptr<DevTool> devTool;

	std::unique_ptr<StageObject> stageObject;
	std::unique_ptr<ObjectCollection> objectCollection; // standalone objects that are not belonged in collision grid
	std::unique_ptr<CollisionGrid> grid;
	std::shared_ptr<Player> player; // Our player need special attention

	Rect GetCurrentArea(base::Vector2 position);
	void SetCurrentCutscene(GameState gameState);
	void LoadMap();
	void Reset(); // after player losing 1 live

	void OnNextMapCutsceneComplete();
	void OnNextRoomCutsceneComplete();

	void ProcessMessage(int message);

	std::unique_ptr<Cutscene> ConstructCutscene(GameState gameState);

	friend class DevTool;
};
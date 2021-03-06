#pragma once

#include "AbstractScene.h"
#include "Stage.h"
#include "GameplayData.h"
#include "MapManager.h"
#include "Hud.h"

class GameplayScene : public AbstractScene
{
public:
	GameplayScene(SceneManager& sceneManager);

	SceneManager& GetSceneManager();
	MapManager& GetMapManager();

	std::shared_ptr<Player> GetPlayer();
	std::shared_ptr<Hud> GetHud();
	std::shared_ptr<GameplayData> GetData();

	void NextStage(Map map, std::string spawnPoint = "Entrypoint");

	void LoadContent() override;
	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;

private:
	std::unique_ptr<Stage> currentStage;
	std::unique_ptr<Stage> nextStage;
	std::unique_ptr<MapManager> mapManager;

	std::shared_ptr<Player> player; // Our player need special attention
	std::shared_ptr<Hud> hud;
	std::shared_ptr<GameplayData> data;
};
#pragma once

#include "Game.h"
#include "SceneManager.h"

class CastlevaniaGame : public Game
{
public:
	CastlevaniaGame();

	void Initialize() override;
	void LoadContent() override;
	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;

private:
	std::unique_ptr<SceneManager> sceneManager;
};
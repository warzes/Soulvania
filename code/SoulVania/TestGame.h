#pragma once

#include "Game.h"
#include "SpriteBatch.h"
#include "Mario.h"

class TestGame : public Game
{
public:
	TestGame();

	void Initialize() override;
	void LoadContent() override;
	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;

private:
	std::unique_ptr<SpriteBatch> spriteBatch;
	std::shared_ptr<Font> gameFont;
	std::shared_ptr<Mario> mario;
};
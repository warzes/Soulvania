#pragma once

#include "Game.h"

class TestGame : public Game
{
public:
	TestGame();

	void Initialize() override;
	void LoadContent() override;
	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;

private:

};
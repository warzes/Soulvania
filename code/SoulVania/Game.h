#pragma once

#include "GameTime.h"
#include "Stopwatch.h"

class Game
{
public:
	void Run();

	virtual void LoadContent();
	virtual void Update(GameTime gameTime);
	virtual void Draw(GameTime gameTime);

protected:
	Game();

	virtual void Initialize();

private:
	bool ProcessEvents();
	void Render(GameTime gameTime);

	void Tick();

	bool initialized = false;

	GameTime gameTime;
	Stopwatch gameTimer;
};
#pragma once

#include "GameTime.h"
#include "Stopwatch.h"
#include "ContentManager.h"

class Game
{
public:
	void Run();

	virtual void LoadContent();
	virtual void Update(GameTime gameTime);
	virtual void Draw(GameTime gameTime);

	ContentManager& GetContent();

protected:
	Game();

	virtual void Initialize();

	std::unique_ptr<ContentManager> content;
	std::shared_ptr<ServiceProvider> service;

private:
	void Render(GameTime gameTime);

	void Tick();

	bool initialized = false;

	GameTime gameTime;
	Stopwatch gameTimer;

	float framePerSecond;
	float tickPerFrame;
};
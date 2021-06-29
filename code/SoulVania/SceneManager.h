#pragma once

#include "Game.h"
#include "AbstractScene.h"
#include "SpriteExtensions.h"
#include "Scene.h"
#include "ObjectFactory.h"

class SceneManager
{
public:
	SceneManager(Game& game);

	ContentManager& GetContent();

	ObjectFactory& GetFactory();
	SpriteExtensions& GetSpriteBatch();

	AbstractScene& SetNextScene(Scene scene);

	void Update(GameTime gameTime);
	void Draw(GameTime gameTime);

private:
	Game& game;
	std::unique_ptr<AbstractScene> currentScene;
	std::unique_ptr<AbstractScene> nextScene;
	std::unique_ptr<ObjectFactory> objectFactory;
	std::unique_ptr<SpriteExtensions> spriteBatch;

	std::unique_ptr<AbstractScene> ConstructScene(Scene scene);
};
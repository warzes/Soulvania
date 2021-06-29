#pragma once

#include "IUpdateable.h"

class SceneManager;

class AbstractScene : public IUpdateable
{
public:
	AbstractScene(SceneManager& sceneManager);

	virtual void LoadContent() = 0;
	virtual void Update(GameTime gameTime) = 0;
	virtual void Draw(GameTime gameTime) = 0;

	virtual ~AbstractScene();

protected:
	SceneManager& sceneManager;
};
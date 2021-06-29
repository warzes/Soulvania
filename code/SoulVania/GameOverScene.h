#pragma once

#include "AbstractScene.h"
#include <raylib/raylib.h>

class GameOverScene : public AbstractScene
{
public:
	GameOverScene(SceneManager& sceneManager);

	void LoadContent() override;
	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;

private:
	std::shared_ptr<Font> font;
	std::shared_ptr<Texture> heartTexture;
	std::string currentOption;

	base::Vector2 gameOverTextPosition;
	base::Vector2 continueTextPosition;
	base::Vector2 endTextPosition;

	base::Vector2 GetHeartPosition();
};
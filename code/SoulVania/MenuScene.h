#pragma once

#include "AnimatedSprite.h"
#include "Stopwatch.h"
#include "AbstractScene.h"

class MenuScene : public AbstractScene
{
public:
	MenuScene(SceneManager& sceneManager);

	void LoadContent() override;
	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;

private:
	enum class State;

	State currentState;
	std::shared_ptr<Texture> background;
	std::shared_ptr<Font> menuFont;
	std::unique_ptr<AnimatedSprite> menuBatSprite;

	std::string startGameText;
	std::string copyrightText;

	base::Vector2 menuBatPosition;
	base::Vector2 startGameTextPosition;
	base::Vector2 copyrightTextPosition;

	Stopwatch transitionTimer;
};
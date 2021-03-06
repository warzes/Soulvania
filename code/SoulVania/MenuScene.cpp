#include "stdafx.h"
#include "MenuScene.h"
#include "SceneManager.h"

constexpr auto TRANSITION_TIME = 800;

enum class MenuScene::State
{
	NORMAL,
	CHANGING_TO_NEXT_SCENE,
};

MenuScene::MenuScene(SceneManager& sceneManager) : AbstractScene{ sceneManager }
{
	startGameText = "PUSH START KEY";

	auto sstream = std::stringstream{};
	sstream
		<< "     TM AND ? 1987\n"
		<< "KONAMI INDUSTRY CO.,LTD.\n"
		<< "       LICENSED BY\n"
		<< "NINTENDO OF AMERICA INC.";

	copyrightText = sstream.str();

	menuBatPosition = base::Vector2{ 367, 191 };
}

void MenuScene::LoadContent()
{
	auto& content = sceneManager.GetContent();
	background = content.Load<Texture>("Backgrounds/Main_Menu.png");
	menuFont = content.Load<Font>("Fonts/MainFont.font.xml");

	auto animationFactory = content.Load<AnimationFactory>("Backgrounds/Menu_Bat.ani.xml");
	menuBatSprite = std::make_unique<AnimatedSprite>(animationFactory);
	menuBatSprite->Play("fly_out");

	auto startGameTextSize = MeasureTextEx(*menuFont, startGameText.c_str(), menuFont->baseSize, 1); // TODO:

	startGameTextPosition.x = (GetScreenWidth() - startGameTextSize.x) / 2;
	startGameTextPosition.y = (GetScreenHeight() - startGameTextSize.y) / 2 + 35;

	copyrightTextPosition.x = startGameTextPosition.x - 80;
	copyrightTextPosition.y = startGameTextPosition.y + 60;
}

void MenuScene::Update(GameTime gameTime)
{
	switch (currentState)
	{
	case State::NORMAL:
		if (IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_SPACE))
		{
			transitionTimer.Start();
			currentState = State::CHANGING_TO_NEXT_SCENE;
		}

		if (menuBatSprite->AnimateComplete())
			menuBatSprite->Play("hover");

		menuBatSprite->Update();
		break;

	case State::CHANGING_TO_NEXT_SCENE:
		if (transitionTimer.ElapsedMilliseconds() >= TRANSITION_TIME)
			sceneManager.SetNextScene(Scene::GAMEPLAY);
		break;
	}
}

void MenuScene::Draw(GameTime gameTime)
{
	auto& spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(0/*D3DXSPRITE_ALPHABLEND*/);

	spriteBatch.Draw(*background, base::Vector2::Zero(), base::Color::White(), false);
	spriteBatch.DrawString(*menuFont, copyrightText, copyrightTextPosition, base::Color::White(), false);
	spriteBatch.Draw(*menuBatSprite, menuBatPosition, false);

	switch (currentState)
	{
	case State::NORMAL:
		spriteBatch.DrawString(*menuFont, startGameText, startGameTextPosition, base::Color::White());
		break;

	case State::CHANGING_TO_NEXT_SCENE:
		spriteBatch.DrawString(*menuFont, startGameText, startGameTextPosition,
			Stopwatch::Every(120) ? base::Color::White() : base::Color::Transparent());
		break;
	}

	spriteBatch.End();
}
#include "stdafx.h"
#include "RenderingSystem.h"
#include "GameObject.h"
#include "Settings.h"
#include "DevTool.h"

std::shared_ptr<Texture> RenderingSystem::bboxTexture = nullptr;

RenderingSystem::RenderingSystem()
{
}

GameObject& RenderingSystem::GetParent()
{
	return GameObject::NullObject();
}

void RenderingSystem::Receive(int message)
{
	switch (message)
	{
	case MOVE_STATE_CHANGED:
		OnMoveStateChanged();
		break;

	case STATE_CHANGED:
		OnStateChanged();
		break;

	case TAKING_DAMAGE:
		OnTakingDamage();
		break;

	}
}

void RenderingSystem::LoadContent(ContentManager& content)
{
	bboxTexture = content.Load<Texture>("Backgrounds/BoundingBox.png");
}

void RenderingSystem::DrawBoundingBox(SpriteExtensions& spriteBatch, RectF boundingBox, base::Color color)
{
	auto position = base::Vector2{ boundingBox.X(), boundingBox.Y() };

	Rect rect = (Rect)boundingBox;

	spriteBatch.Draw(*bboxTexture, position, &rect, color, 0.0f, base::Vector2::One(), SpriteEffects::None);
}

void RenderingSystem::Update(GameTime gameTime)
{
}

void RenderingSystem::Draw(SpriteExtensions& spriteBatch)
{
	if (DrawDebug())
	{
		auto boundingBox = GetSprite().GetBoundingRectangle(GetParent().GetPosition());
		auto color = GetBoundingBoxColor();

		DrawBoundingBox(spriteBatch, boundingBox, color);
	}
}

bool RenderingSystem::DrawDebug()
{
	if (DevTool::IsDebugging && GetParent().GetSprite()->IsVisible())
		return true;
	else
		return false;
}

void RenderingSystem::OnMoveStateChanged()
{
}

void RenderingSystem::OnStateChanged()
{
}

void RenderingSystem::OnTakingDamage()
{
}

base::Color RenderingSystem::GetBoundingBoxColor()
{
	auto objectId = GetParent().GetId();
	auto bboxColorScale = 0.65f;

	switch (objectId)
	{
	case ObjectId::Block:
		return base::Color::DimGray() * bboxColorScale;

	case ObjectId::SpawnArea:
	case ObjectId::SpawnPoint:
		return base::Color::Red() * (bboxColorScale - 0.2f);

	case ObjectId::BossFightArea:
		return base::Color::DimGray() * (bboxColorScale - 0.3f);

	case ObjectId::WaterArea:
		return base::Color::Blue() * bboxColorScale;

	case ObjectId::Player:
		return base::Color::Gold() * bboxColorScale;

	case ObjectId::Brazier:
	case ObjectId::Candle:
		return base::Color::YellowGreen() * bboxColorScale;

	case ObjectId::Zombie:
	case ObjectId::Panther:
	case ObjectId::VampireBat:
	case ObjectId::Fishman:
		return base::Color::Green();

	case ObjectId::Whip:
		return base::Color::Red() * bboxColorScale;

		// Just a fg image, skip drawing
	case ObjectId::Castle:
	case ObjectId::StageArea:
		return base::Color::Transparent();

	default:
		return base::Color::Magenta() * bboxColorScale;
	}
}